
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>

void otp_init(struct bcm2835_emul *emul) {
	/* TODO */
	memset(&emul->otp,0, sizeof(emul->otp));
	(void)emul;
}
uint32_t otp_load(struct bcm2835_emul *emul, uint32_t address) {
//	if (address == VC_OTP0__ADDRESS + 0x0) {
//		return 0x1020000a;
//	}
//	/* TODO */
	if (address == VC_OTP0_OTP_BOOTMODE_REG) {
	} else if (address == VC_OTP0_OTP_CONFIG_REG) {
	} else if (address == VC_OTP0_OTP_CTRL_LOW_REG) {
	} else if (address == VC_OTP0_OTP_CTRL_HIGH_REG) {
	} else if (address == VC_OTP0_OTP_STATUS_REG) {
	} else if (address == VC_OTP0_OTP_BITSEL_REG) {
	} else if (address == VC_OTP0_OTP_DATA_REG) {
	} else if (address == VC_OTP0_OTP_ADDR_REG) {
	} else if (address == VC_OTP0_OTP_WRITE_DATA_READ_REG) {
	} else if (address == VC_OTP0_OTP_INIT_STATUS_REG) {
	} else {
	/* TODO */
		print_log("otp_load address: %x", address);
		assert(0 && "OTP Load not implemented!\n");
	}
	return 0x1020000a;

	(void)emul;
	(void)address;
}
void otp_store(struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
	/* TODO */
	if (address == VC_OTP0_OTP_BOOTMODE_REG) {
		print_log("BOOTMODE");
	} else if (address == VC_OTP0_OTP_CONFIG_REG) {
		print_log("control");
	} else if (address == VC_OTP0_OTP_CTRL_LOW_REG) {
		print_log("control low");
	} else if (address == VC_OTP0_OTP_CTRL_HIGH_REG) {
		print_log("control high");
	} else if (address == VC_OTP0_OTP_STATUS_REG) {
		print_log("status");
	} else if (address == VC_OTP0_OTP_BITSEL_REG) {
		print_log("bitsel");
	} else if (address == VC_OTP0_OTP_DATA_REG) {
		print_log("data");
	} else if (address == VC_OTP0_OTP_ADDR_REG) {
		print_log("addr");
	} else if (address == VC_OTP0_OTP_WRITE_DATA_READ_REG) {
		print_log("write data read");
	} else if (address == VC_OTP0_OTP_INIT_STATUS_REG) {
		print_log("init status");
	} else {
	        printf("otp_store address: %x, value %x:", address, value);
		assert(0 && "OTP Store not implemented!\n");
	}
	(void)emul;
	(void)address;
	(void)value;
}

