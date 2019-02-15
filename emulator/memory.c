
#include "bcm2835_emul.h"
#include "vc4_emul.h"
#include "vcregs.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define DRAM_SIZE (512 * 1024 * 1024)
#define BOOTROM_SIZE (64 * 1024)
#define BOOTROM_ADDRESS_END (BOOTROM_BASE_ADDRESS + BOOTROM_SIZE)
#define SIZE_64KB 0xffff
#define SIZE_1GB 0x3fffffff

void print_log(const char *fmt, ...);

struct device_region {
	uint32_t address;
	uint32_t size;
	uint32_t (*load)(struct bcm2835_emul *emul, uint32_t address);
	void (*store)(struct bcm2835_emul *emul, uint32_t address, uint32_t value);
};

static const struct device_region devices[] = {
	{ VC_MULT__ADDRESS, VC_MULT__SIZE, mult_load, mult_store },     	/* 0x7e000000 */ // MS (Not enabled in default code)
//	{ VC_CCPT__ADDRESS, VC_CCPT__SIZE, ccpt_load, ccpt_store },     	/* 0x7e001000 */ // CCP2TX
	{ VC_INTE__ADDRESS, VC_INTE__SIZE, inte_load, inte_store },     	/* 0x7e002000 */ // IC0, IC1
	{ VC_TIMER__ADDRESS, VC_TIMER__SIZE, timer_load, timer_store }, 	/* 0x7e003000 */ // ST
//	{ VC_TXP__ADDRESS, VC_TXP__SIZE, txp_load, txp_store }, 		/* 0x7e004000 */
//	{ VC_JPEG__ADDRESS, VC_JPEG__SIZE, jpeg_load, jpeg_store }, 		/* 0x7e005000 */ // JP
//	{ VC_MPHI__ADDRESS, VC_MPHI__SIZE, mphi_load, mphi_store }, 		/* 0x7e006000 */
//	{ VC_DMA__ADDRESS, VC_DMA__SIZE, dma_load, dma_store }, 		/* 0x7e007000 */ // DMA0-14
//	{ VC_NU__ADDRESS, VC_NU__SIZE, nu_load, nu_store }, 			/* 0x7e008000 */
//	{ VC_ARBA__ADDRESS, VC_ARBA__SIZE, arba_load, arba_store }, 		/* 0x7e009000 */ // SYSAC/APERF0
//	{ VC_BRDG__ADDRESS, VC_BRDG__SIZE, brdg_load, brdg_store }, 		/* 0x7e00a000 */ // ASB
//	{ VC_ARMCB__ADDRESS, VC_ARMCB__SIZE, armcb_load, armcb_store },		/* 0x7e00b000 */ // ARM
	{ VC_PM__ADDRESS, VC_PM__SIZE, pm_load, pm_store },             	/* 0x7e100000 */ // Not enabled in default code
	{ VC_CM__ADDRESS, VC_CM__SIZE, cm_load, cm_store },             	/* 0x7e101000 */
	{ VC_A2W__ADDRESS, VC_A2W__SIZE, a2w_load, a2w_store },         	/* 0x7e102000 */ // Not Enabled in default code
//	{ VC_AVS__ADDRESS, VC_AVS__SIZE, avs_load, avs_store },         	/* 0x7e103000 */
//	{ VC_RNG__ADDRESS, VC_RNG__SIZE, rng_load, rng_store },         	/* 0x7e104000 */
	{ VC_GPIO__ADDRESS, VC_GPIO__SIZE, gpio_load, gpio_store },     	/* 0x7e200000 */ // GP
//	{ VC_UART0__ADDRESS, VC_UART0__SIZE, uart0_load, uart0_store }, 	/* 0x7e201000 */
	{ VC_ALTMMC__ADDRESS, VC_ALTMMC__SIZE, mmc_load, mmc_store },   	/* 0x7e202000 */ // SH
//	{ VC_PCM__ADDRESS, VC_PCM__SIZE, pcm_load, pcm_store },  		/* 0x7e203000 */
//	{ VC_SPI0__ADDRESS, VC_SPI0__SIZE, spi0_load, spi0_store },     	/* 0x7e204000 */ // SPI
//	{ VC_BSC0__ADDRESS, VC_BSC0__SIZE, bsc0_load, bsc0_store },     	/* 0x7e205000 */ // I2C0
//	{ VC_PIXV0__ADDRESS, VC_PIXV0__SIZE, pixv0_load, pixv0_store },     	/* 0x7e206000 */ // PIXELVALVE0
//	{ VC_PIXV1__ADDRESS, VC_PIXV1__SIZE, pixv1_load, pixv1_store },  	/* 0x7e207000 */ // PIXELVALVE1
//	{ VC_DPI__ADDRESS, VC_DPI__SIZE, dpi_load, dpi_store },			/* 0x7e208000 */
//	{ VC_DSI0__ADDRESS, VC_DSI0__SIZE, dsi0_load, dsi0_store },		/* 0x7e209000 */
//	{ VC_TB__ADDRESS, VC_TB__SIZE, tb_load, tb_store },			/* 0x7e20b000 */ // TB/TBE 
//	{ VC_PWM0__ADDRESS, VC_PWM0__SIZE, pwm0_load, pwm0_store },   		/* 0x7e20c000 */ // PWM
//	{ VC_PERM__ADDRESS, VC_PERM__SIZE, perm_load, perm_store },   		/* 0x7e20d000 */ // PRM
//	{ VC_TEC__ADDRESS, VC_TEC__SIZE, tec_load, tec_store },   		/* 0x7e20e000 */ // TE
	{ VC_OTP0__ADDRESS, VC_OTP0__SIZE, otp_load, otp_store },       	/* 0x7e20f000 */ // OTP
//	{ VC_SLIM__ADDRESS, VC_SLIM__SIZE, slim_load, slim_store },     	/* 0x7e210000 */
//	{ VC_CPG__ADDRESS, VC_CPG__SIZE, cpg_load, cpg_store },         	/* 0x7e211000 */
//	{ VC_TS__ADDRESS, VC_TS__SIZE, ts_load, ts_store }, 			/* 0x7e212000 */
//	{ VC_AVSP__ADDRESS, VC_AVSP__SIZE, avsp_load, avsp_store },     	/* 0x7e213000 */
//	{ VC_I2CSPISLV__ADDRESS, VC_I2CSPISLV__SIZE, i2cspislv_load, i2cspislv_store }, /* 0x7e214000 */ // I2C_SPI_SLV
	{ VC_AUX__ADDRESS, VC_AUX__SIZE, aux_load, aux_store },         	/* 0x7e215000 */
//	{ VC_AVEOUT__ADDRESS, VC_AVEOUT__SIZE, aveout_load, aveout_store },	/* 0x7e240000 */
//	{ VC_EMMC__ADDRESS, VC_EMMC__SIZE, emmc_load, emmc_store },     	/* 0x7e300000 */
//	{ VC_DDRV__ADDRESS, VC_DDRV__SIZE, ddrv_load, ddrv_store },     	/* 0x7e400000 */ // SCALER
//	{ VC_SMI__ADDRESS, VC_SMI__SIZE, smi_load, smi_store },         	/* 0x7e600000 */
//	{ VC_DSI1__ADDRESS, VC_DSI1__SIZE, dsi1_load, dsi1_store },     	/* 0x7e700000 */
//	{ VC_CAM0__ADDRESS, VC_CAM0__SIZE, cam0_load, cam0_store },     	/* 0x7e800000 */
//	{ VC_CAM1__ADDRESS, VC_CAM1__SIZE, cam1_load, cam1_store },     	/* 0x7e801000 */
//	{ VC_CMI__ADDRESS, VC_CMI__SIZE, cmi_load, cmi_store },     		/* 0x7e802000 */
//	{ VC_BSC1__ADDRESS, VC_BSC1__SIZE, bsc1_load, bsc1_store },     	/* 0x7e804000 */ // I2C1
//	{ VC_BSC2__ADDRESS, VC_BSC2__SIZE, bsc2_load, bsc2_store },     	/* 0x7e805000 */ // I2C2
//	{ VC_VEC__ADDRESS, VC_VEC__SIZE, vec_load, vec_store },    		/* 0x7e806000 */
//	{ VC_PIXV2__ADDRESS, VC_PIXV2__SIZE, pixv2_load, pixv2_store },		/* 0x7e807000 */ // PIXELVALVE2
//	{ VC_HD__ADDRESS, VC_HD__SIZE, hd_load, hd_store },    			/* 0x7e808000 */
//	{ VC_HDCP__ADDRESS, VC_HDCP__SIZE, hdcp_load, hdcp_store },    		/* 0x7e809000 */
//	{ VC_PIARBCTL__ADDRESS, VC_PIARBCTL__SIZE, piarbctl_load, piarbctl_store }, /* 0x7e80a000 */
//	{ VC_HDMI__ADDRESS, VC_HDMI__SIZE, hdmi_load, hdmi_store },    		/* 0x7e902000 */
//	{ VC_AVEIN__ADDRESS, VC_AVEIN__SIZE, avein_load, avein_store }, 	/* 0x7e910000 */
//	{ VC_USB__ADDRESS, VC_USB__SIZE, usb_load, usb_store },         	/* 0x7e980000 */
//	{ VC_ISP__ADDRESS, VC_ISP__SIZE, isp_load, isp_store },         	/* 0x7ea00000 */
//	{ VC_V3D__ADDRESS, VC_V3D__SIZE, v3d_load, v3d_store },         	/* 0x7ec00000 */
	{ VC_SDCO__ADDRESS, VC_SDCO__SIZE, sdco_load, sdco_store },     	/* 0x7ee00000 */ // SD (Not Enabled in default code)
//	{ VC_L2CC__ADDRESS, VC_L2CC__SIZE, l2cc_load, l2cc_store },     	/* 0x7ee01000 */ // L2
//	{ VC_L1CC__ADDRESS, VC_L1CC__SIZE, l1cc_load, l1cc_store },     	/* 0x7ee02000 */ // L1
//	{ VC_ARBR__ADDRESS, VC_ARBR__SIZE, arbr_load, arbr_store },     	/* 0x7ee04000 */ // VPU_ARB_CTL
//	{ VC_DMA15__ADDRESS, VC_DMA15__SIZE, dma15_load, dma15_store }, 	/* 0x7ee05000 */
//	{ VC_APHYCSR__ADDRESS, VC_APHYCSR__SIZE, aphycsr_load, aphycsr_store }, /* 0x7ee06000 */ // APHY_CSR
//	{ VC_DCRC__ADDRESS, VC_DCRC__SIZE, dcrc_load, dcrc_store },     	/* 0x7ee07000 */ // DPHY_CSR
//	{ VC_AXIP__ADDRESS, VC_AXIP__SIZE, axip_load, axip_store },     	/* 0x7ee08000 */ // APERF1
//	{ VC_H264__ADDRESS, VC_H264__SIZE, h264_load, h264_store },     	/* 0x7f000000 */
//	{ VC_VCE__ADDRESS, VC_VCE__SIZE, vce_load, vce_store },  	   	/* 0x7f100000 */
};

#define DEVICE_COUNT (sizeof(devices) / sizeof(devices[0]))

static int is_in_region(uint32_t address,
                        uint32_t size,
                        uint32_t start,
                        uint32_t end) {
	if (address < start || (uint64_t)address + size > end) {
		return 0;
	} else {
		return 1;
	}
}

void memory_init(struct bcm2835_emul *emul) {
	emul->dram = malloc(DRAM_SIZE);
	/* ROM and bootram (actually just cache?) are stored here */
	emul->bootram = malloc(BOOTROM_SIZE);
}

void memory_fill(struct bcm2835_emul *emul,
                 uint32_t address,
                 const void *data,
                 size_t size) {
	if (is_in_region(address, size, BOOTROM_BASE_ADDRESS, BOOTROM_ADDRESS_END)) {
		char *dest = emul->bootram + (address - BOOTROM_BASE_ADDRESS);
		memcpy(dest, data, size);
	} else if (is_in_region(address & SIZE_1GB, size, 0x0, DRAM_SIZE)) {
		char *dest = emul->dram + (address & SIZE_1GB);
		memcpy(dest, data, size);
	} else {
		assert(0 && "memory_fill: Invalid memory area!");
	}
}

uint32_t vc4_emul_load(void *user_data,
                       uint32_t address,
                       int size) {
	struct bcm2835_emul *emul = user_data;
	uint32_t value;
	unsigned int i;
	if (is_in_region(address, size, BOOTROM_BASE_ADDRESS, BOOTROM_ADDRESS_END)) {
		value = *(uint32_t*)(emul->bootram + (address & SIZE_64KB));
	} else if (is_in_region(address & SIZE_1GB, size, 0x0, DRAM_SIZE)) {
		value = *(uint32_t*)(emul->dram + (address & SIZE_1GB));
	} else {
		/* device registers */
		if (size == 4 && (address & 3) == 0) {
			for (i = 0; i < DEVICE_COUNT; i++) {
				if (address >= devices[i].address &&
						address <= devices[i].address + devices[i].size) {
					uint32_t value = devices[i].load(emul, address);
//					print_log("MMIO(R, 4) %08x => %08x\n", address, value);
					return value;
				}
			}
		}
		/* TODO: interrupt number? */
//		print_log("address was: %x, size was %x", address, size);
		vc4_emul_interrupt(emul->vc4, 0, "Invalid load address.");
	}
	value &= 0xffffffff >> ((4 - size) * 8);
	/*print_log("load %08x %08x\n", address, value);*/
	return value;
}

void vc4_emul_store(void *user_data,
                    uint32_t address,
                    int size,
                    uint32_t value) {
	struct bcm2835_emul *emul = user_data;
	char *dest;
	unsigned int i;
//	print_log("store %08x %08x\n", address, value);
	if (is_in_region(address, size, BOOTROM_BASE_ADDRESS, BOOTROM_ADDRESS_END)) {
		dest = emul->bootram + (address & SIZE_64KB);
	} else if (is_in_region(address & SIZE_1GB, size, 0x0, DRAM_SIZE)) {
		dest = emul->dram + (address & SIZE_1GB);
	} else {
		/* device registers */
		if (size == 4 && (address & 3) == 0) {
			for (i = 0; i < DEVICE_COUNT; i++) {
				if (address >= devices[i].address &&
						address <= devices[i].address + devices[i].size) {
//					print_log("MMIO(W, 4) %08x <= %08x\n", address, value);
					return devices[i].store(emul, address, value);
				}
			}
		}
		/* TODO: interrupt number? */
		char message[36];
		sprintf(message, "Invalid store address: 0x%08x\n", address);
		vc4_emul_interrupt(emul->vc4, 0, message);
	}
	switch (size) {
		case 1:
			*(uint8_t*)dest = value;
			break;
		case 2:
			*(uint16_t*)dest = value;
			break;
		case 4:
			*(uint32_t*)dest = value;
			break;
		default:
			assert(0 && "Invalid store size.");
	}
}

