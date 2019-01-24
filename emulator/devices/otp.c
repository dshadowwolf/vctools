
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>
#include <malloc.h>

extern void print_log(const char *fmt, ...);

void otp_init(struct bcm2835_emul *emul) {
	/* TODO */
	memset(&emul->otp,0, sizeof(emul->otp));
	emul->otp.registers[0] =0x1020000A;
	emul->otp.otp_memory = malloc(sizeof(uint32_t)*0x80);
	memset(emul->otp.otp_memory, 0, 0x80*sizeof(uint32_t));
	emul->otp.otp_memory[0x10] = 0x00280000;
	emul->otp.otp_memory[0x11] = 0x1020000a;
	emul->otp.otp_memory[0x12] = 0x1020000a;
}

uint32_t otp_load(struct bcm2835_emul *emul, uint32_t address) {
  uint32_t work = address;
  work &= 0x000000FF;
  work /= 4; 
  print_log("otp_load address: %x", address);
  assert(work > 9 && "Unknown OTP Register!\n");
  return emul->otp.registers[work];
}

void otp_store(struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  uint32_t work = address;
  work &= 0x000000FF;
  work /= 4;
  
  print_log("otp_store address: %x", address);
  assert(work > 9 && "Unknown OTP Register!\n");
  
  emul->otp.registers[work] = value;
  
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
    emul->otp.registers[6] = emul->otp.otp_memory[value];
  } else if (address == VC_OTP0_OTP_WRITE_DATA_READ_REG) {
    print_log("write data read -> 0x%08X", value);
  } else if (address == VC_OTP0_OTP_INIT_STATUS_REG) {
    print_log("init status -> 0x%08X", value);
  }
}

