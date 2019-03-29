
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

#define GET_REG(reg) registers[(reg)>0?(reg):((reg)/4)]

uint32_t registers[21] = { 0, 0, 0, 0,  // 0x00 to 0x0c
  0, 0, 0, 0,                   // 0x10 to 0x1c
  0, 0, 0, 0,                   // 0x20 to 0x2c
  0, 0, 0, 0,                   // 0x30 to 0x3c
  0, 0, 0, 0,                   // 0x40 to 0x5c
  0
};                              //0x50

/*
 * COMMAND REGISTER (0x00):
 * 31:16 ignored ?
 * 15 	Enable 	R/W 	Set this to 1 to when executing a command, it will reset itself to 0 when the command has finished executing.
 * 14 	Fail Flag
 * 13
 * 12
 * 11 	Busy 	?/W 	Set this to zero when executing TRANSFER_STOP or one when executing READ_MULTIPLE_BLOCKS
 * 10 	No Response
 * 9 	Long Response
 * 8
 * 7 	Write
 * 6 	Read
 * 5:0 	Command 	?/W 	The command according to the MMC spec.
 *
 * STATUS REGISTER (0x20):
 * 31:1 	? 		Bits 7:5 and 3 are sometimes returned from a function.
 * 0 	FIFO Status 	RO 	Set when there is data in the FIFO (Data Register 0x40)
 */

/*
 * From the Linux driver, this is an expected reset sequence:
 *
 * put SDVDD_POWER_OFF (0) in register SDVDD (0x30)          (power control)
 * put 0 in SDCMD (0x00) and in SDARG (0x04)                 (command and parameter)
 * put 0xf00000 in SDTOUT (0x08)                             (timeout counter, starting value)
 * put 0 in SDCDIV (0x0c)                                    (starting clock divider)
 * put 0x7f8 in SDHSTS (0x20)                                (host status)
 * put 0 in SDHCFG (0x38), SDHBCT (0x3c) and SDHBLC (0x50)   (host config, host byte count, host block count)
 * load SDEDM (0x34)                                         (emergency debug mode)
 * mask ((SDEDM_THRESHOLD_MASK << SDEDM_READ_THRESHOLD_SHIFT) | (SDEDM_THRESHOLD_MASK << SDEDM_WRITE_THRESHOLD_SHIFT))
 *   -- set (FIFO_READ_THRESHOLD << SDEDM_READ_THRESHOLD_SHIFT) | (FIFO_WRITE_THRESHOLD << SDEDM_WRITE_THRESHOLD_SHIFT);
 * write back to SDEDM (0x34)
 * wait for 20ms
 * write 1 to SDVDD
 * wait for 20ms
 * set SDHCFG (0x38) and SDCDIV (0x0c) to expected values
 */

/*

  94     object_initialize(&s->sdhci, sizeof(s->sdhci), TYPE_SYSBUS_SDHCI);
  95     object_property_add_child(obj, "sdhci", OBJECT(&s->sdhci), NULL);
  96     qdev_set_parent_bus(DEVICE(&s->sdhci), sysbus_get_default());

  99     object_initialize(&s->sdhost, sizeof(s->sdhost), TYPE_BCM2835_SDHOST);
 100     object_property_add_child(obj, "sdhost", OBJECT(&s->sdhost), NULL);
 101     qdev_set_parent_bus(DEVICE(&s->sdhost), sysbus_get_default());

 257     /* Extended Mass Media Controller
 258      *
 259      * Compatible with:
 260      * - SD Host Controller Specification Version 3.0 Draft 1.0
 261      * - SDIO Specification Version 3.0
 262      * - MMC Specification Version 4.4
 263      *
 264      * For the exact details please refer to the Arasan documentation:
 265      *   SD3.0_Host_AHB_eMMC4.4_Usersguide_ver5.9_jan11_10.pdf
 266      * /
 267     object_property_set_uint(OBJECT(&s->sdhci), 3, "sd-spec-version", &err);
 268     object_property_set_uint(OBJECT(&s->sdhci), BCM2835_SDHC_CAPAREG, "capareg",
 269                              &err);
 270     object_property_set_bool(OBJECT(&s->sdhci), true, "pending-insert-quirk",
 271                              &err);
 272     if (err) {
 273         error_propagate(errp, err);
 274         return;
 275     }
 276
 277     object_property_set_bool(OBJECT(&s->sdhci), true, "realized", &err);
 278     if (err) {
 279         error_propagate(errp, err);
 280         return;
 281     }
 282
 283     memory_region_add_subregion(&s->peri_mr, EMMC_OFFSET,
 284                 sysbus_mmio_get_region(SYS_BUS_DEVICE(&s->sdhci), 0));
 285     sysbus_connect_irq(SYS_BUS_DEVICE(&s->sdhci), 0,
 286         qdev_get_gpio_in_named(DEVICE(&s->ic), BCM2835_IC_GPU_IRQ,
 287                                INTERRUPT_ARASANSDIO));

 289     /* SDHOST * /
 290     object_property_set_bool(OBJECT(&s->sdhost), true, "realized", &err);
 291     if (err) {
 292         error_propagate(errp, err);
 293         return;
 294     }
 295
 296     memory_region_add_subregion(&s->peri_mr, MMCI0_OFFSET,
 297                 sysbus_mmio_get_region(SYS_BUS_DEVICE(&s->sdhost), 0));
 298     sysbus_connect_irq(SYS_BUS_DEVICE(&s->sdhost), 0,
 299         qdev_get_gpio_in_named(DEVICE(&s->ic), BCM2835_IC_GPU_IRQ,
 300                                INTERRUPT_SDIO));

  21 /* Capabilities for SD controller: no DMA, high-speed, default clocks etc. * /
  22 #define BCM2835_SDHC_CAPAREG 0x52134b4

 */

int
mmc_init (struct bcm2835_emul *emul, const char *sdcard_file) {
  /*
   * TODO 
   */
  memset (&emul->mmc, 0, sizeof (emul->mmc));
  return 0;
  (void) sdcard_file;
}

uint32_t
mmc_load (struct bcm2835_emul *emul, uint32_t address) {
  /*
   * TODO 
   */
  print_log ("MMC load address: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
mmc_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  /*
   * TODO 
   */
  print_log ("MMC store address: 0x%08x: 0x%08x\n", address, value);
  (void) emul;
}
