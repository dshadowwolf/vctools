
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log(const char *fmt, ...);
void otp_init(struct bcm2835_emul *emul) {
	/* TODO */
	memset(&emul->otp,0, sizeof(emul->otp));
	emul->otp.registers[0] =0x1020000A;
	(void)emul;
}
uint32_t otp_load(struct bcm2835_emul *emul, uint32_t address) {
//	if (address == VC_OTP0__ADDRESS + 0x0) {
//		return 0x1020000a;
//	}
//	/* TODO */
  uint32_t work = address;
  work &= 0x000000FF;
  work /= 4;
  if(work > 6) {
    print_log("otp_load address: %x", address);
    assert(0 && "OTP Load not implemented!\n");
  } else {
    return emul->otp.registers[work];
  }
}

void otp_store(struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  uint32_t work = address;
  work &= 0x000000FF;
  work /= 4;
  emul->otp.registers[work] = value;
  
	/* TODO */
	if (address == VC_OTP0_OTP_BOOTMODE_REG) {
	  print_log("BOOTMODE -> 0x%08X", value);
	} else if (address == VC_OTP0_OTP_CONFIG_REG) {
		print_log("control -> 0x%08X", value);
	} else if (address == VC_OTP0_OTP_CTRL_LOW_REG) {
		print_log("control low -> 0x%08X", value);
	} else if (address == VC_OTP0_OTP_CTRL_HIGH_REG) {
		print_log("control high -> 0x%08X", value);
	} else if (address == VC_OTP0_OTP_STATUS_REG) {
		print_log("status -> 0x%08X", value);
	} else if (address == VC_OTP0_OTP_BITSEL_REG) {
		print_log("bitsel -> 0x%08X", value);
	} else if (address == VC_OTP0_OTP_DATA_REG) {
		print_log("data -> 0x%08X", value);
	} else if (address == VC_OTP0_OTP_ADDR_REG) {
		print_log("addr -> 0x%08X", value);
	} else if (address == VC_OTP0_OTP_WRITE_DATA_READ_REG) {
		print_log("write data read -> 0x%08X", value);
	} else if (address == VC_OTP0_OTP_INIT_STATUS_REG) {
		print_log("init status -> 0x%08X", value);
	} else {
	        print_log("otp_store address: %x, value %x:", address, value);
		assert(0 && "OTP Store not implemented!\n");
	}
}

