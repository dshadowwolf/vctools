
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log(const char *fmt, ...);

static const uint32_t clock_address[] = {
	VC_CM_GNRIC_CTL,
	VC_CM_VPU_CTL,
	VC_CM_SYS_CTL,
	VC_CM_PERIA_CTL,
	VC_CM_PERII_CTL,
	VC_CM_H264_CTL,
	VC_CM_ISP_CTL,
	VC_CM_V3D_CTL,
	VC_CM_CAM0_CTL,
	VC_CM_CAM1_CTL,
	VC_CM_DSI0E_CTL,
	VC_CM_DSI0P_CTL,
	VC_CM_DPI_CTL,
	VC_CM_GP_CTL(0),
	VC_CM_GP_CTL(1),
	VC_CM_GP_CTL(2),
	VC_CM_HSM_CTL,
	VC_CM_OTP_CTL,
	VC_CM_PCM_CTL,
	VC_CM_PWM_CTL,
	VC_CM_SLIM_CTL,
	VC_CM_SMI_CTL,
	VC_CM_TCNT_CTL,
	VC_CM_TEC_CTL,
	VC_CM_TD0_CTL,
	VC_CM_TD1_CTL,
	VC_CM_TSENS_CTL,
	VC_CM_TIMER_CTL,
	VC_CM_UART_CTL,
	VC_CM_VEC_CTL,
	VC_CM_BURST_CTL,
	VC_CM_DSI1E_CTL,
	VC_CM_DSI1P_CTL,
	VC_CM_DFT_CTL,
	VC_CM_PULSE_CTL,
	VC_CM_SDC_CTL,
	VC_CM_ARM_CTL,
	VC_CM_AVEO_CTL,
	VC_CM_EMMC_CTL,
};

void cm_init(struct bcm2835_emul *emul) {
	memset(&emul->cm, 0, sizeof(emul->cm));
}
uint32_t cm_load(struct bcm2835_emul *emul, uint32_t address) {
	int i;
	if (address == VC_CM_PLLC) {
		return emul->cm.pllc;
	} else if (address == VC_CM_PLLD) {
		return emul->cm.plld;
	} else if (address == VC_CM_LOCK) {
		return emul->cm.lock;
	}
	for (i = 0; i < CLOCK_COUNT; i++) {
		if (address == clock_address[i]) {
			return emul->cm.clocks[i].control;
		}
		if (address == clock_address[i] + 4) {
			return emul->cm.clocks[i].divisor;
		}
	}
	print_log("CM Load Address: 0x%08x\n", address); 
	assert(0 && "Unknown CM register!\n");
	return 0;
}
void cm_store(struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
	int i;
	/* all registers need the password field */
	if ((value >> 24) != 0x5a) {
		return;
	}
	if (address == VC_CM_PLLC) {
		emul->cm.pllc = value;
		return;
	} else if (address == VC_CM_PLLD) {
		emul->cm.plld = value;
		return;
	} else if (address == VC_CM_LOCK) {
		emul->cm.lock = value;
		return;
	}
	for (i = 0; i < CLOCK_COUNT; i++) {
		if (address == clock_address[i]) {
			/* TODO */
			emul->cm.clocks[i].control = value;
			return;
		}
		if (address == clock_address[i] + 4) {
			/* TODO */
			emul->cm.clocks[i].divisor = value;
			return;
		}
	}
	print_log("CM Store Address: 0x%08x, 0x%08x\n", address, value);
	assert(0 && "Unknown CM register!\n");
}

