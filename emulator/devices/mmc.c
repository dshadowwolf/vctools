
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

#define GET_REG(reg) registers[(reg)>0?(reg):((reg)/4)]

uint32_t registers[21] = { 0, 0, 0, 0, // 0x00 to 0x0c
						 0, 0, 0, 0, // 0x10 to 0x1c
						 0, 0, 0, 0, // 0x20 to 0x2c
						 0, 0, 0, 0, // 0x30 to 0x3c
						 0, 0, 0, 0, // 0x40 to 0x5c
						 0 }; //0x50

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
mmc_load (struct bcm2835_emul * emul, uint32_t address) {
  /*
   * TODO 
   */
  print_log("MMC load address: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
mmc_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  /*
   * TODO 
   */
  print_log("MMC store address: 0x%08x: 0x%08x\n", address, value);
  (void) emul;
}
