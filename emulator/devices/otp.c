
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

#ifndef BOOTMODE
#define BOOTMODE 0x1020000A
#endif

#define BOOTSIGN_BLANK 0xffffffff
#ifndef BOOTSIGN_0
#define BOOTSIGN_0 BOOTSIGN_BLANK
#endif
#ifndef BOOTSIGN_1
#define BOOTSIGN_1 BOOTSIGN_BLANK
#endif
#ifndef BOOTSIGN_2
#define BOOTSIGN_2 BOOTSIGN_BLANK
#endif
#ifndef BOOTSIGN_3
#define BOOTSIGN_3 BOOTSIGN_BLANK
#endif
#ifndef PARITY_ROW
#define PARITY_ROW 0x00002727
#endif

#ifndef CONTROL
#define CONTROL 0x00280000
#endif

#ifndef SERIAL_NUM
#define SERIAL_NUM 0xac546a6d
#endif
#ifndef SERIAL_INV
#define SERIAL_INV 0x53ab9592
#endif
#ifndef BOARD_REV
#define BOARD_REV 0x00a220a0
#endif

extern void print_log (const char *fmt, ...);

void
otp_init (struct bcm2835_emul *emul) {
  /*
   * TODO 
   */
  memset (&emul->otp, 0, sizeof (emul->otp));
  emul->otp.registers[0] = BOOTMODE;
  emul->otp.otp_memory = malloc (sizeof (uint32_t) * 0x80);
  memset (emul->otp.otp_memory, 0, 0x80 * sizeof (uint32_t));
  emul->otp.otp_memory[0x10] = CONTROL; // 16 - M - OTP_CONTROL_ROW
  emul->otp.otp_memory[0x11] = BOOTMODE;  // 17 - M - Bootmode Register
  emul->otp.otp_memory[0x12] = BOOTMODE;  // 18 - M - Bootmode Register (Copy)
  emul->otp.otp_memory[0x13] = BOOTSIGN_0;  // 19 - M - OTP_BOOT_SIGNING_KEY_ROW_0
  emul->otp.otp_memory[0x14] = BOOTSIGN_1;  // 20 - M - OTP_BOOT_SIGNING_KEY_ROW_1
  emul->otp.otp_memory[0x15] = BOOTSIGN_2;  // 21 - M - OTP_BOOT_SIGNING_KEY_ROW_2
  emul->otp.otp_memory[0x16] = BOOTSIGN_3;  // 22 - M - OTP_BOOT_SIGNING_KEY_ROW_3
  emul->otp.otp_memory[0x17] = BOOTSIGN_0;  // 23 - M - OTP_BOOT_SIGNING_KEY_ROW_REDUNDANT_0
  emul->otp.otp_memory[0x18] = BOOTSIGN_1;  // 24 - M - OTP_BOOT_SIGNING_KEY_ROW_REDUNDANT_1
  emul->otp.otp_memory[0x19] = BOOTSIGN_2;  // 25 - M - OTP_BOOT_SIGNING_KEY_ROW_REDUNDANT_2
  emul->otp.otp_memory[0x1a] = BOOTSIGN_3;  // 26 - M - OTP_BOOT_SIGNING_KEY_ROW_REDUNDANT_3
  emul->otp.otp_memory[0x1b] = PARITY_ROW;  // 27 - M - OTP_BOOT_SIGNING_PARITY_ROW
  emul->otp.otp_memory[0x1c] = SERIAL_NUM;  // 28 - M - Serial Number
  emul->otp.otp_memory[0x1d] = SERIAL_INV;  // 29 - M - ~Serial Number
  emul->otp.otp_memory[0x1e] = BOARD_REV; // 30 - M - Board Revision
  emul->otp.otp_memory[0x1f] = 0x00000000;  // 31 - O - Batch Number
  emul->otp.otp_memory[0x20] = 0x00000000;  // 32 - O - Overclock Protection
  emul->otp.otp_memory[0x24] = 0x00000000;  // 36 - O - Customer OTP 0
  emul->otp.otp_memory[0x25] = 0x00000000;  // 37 - O - Customer OTP 1
  emul->otp.otp_memory[0x26] = 0x00000000;  // 38 - O - Customer OTP 2
  emul->otp.otp_memory[0x27] = 0x00000000;  // 39 - O - Customer OTP 3
  emul->otp.otp_memory[0x28] = 0x00000000;  // 40 - O - Customer OTP 4
  emul->otp.otp_memory[0x29] = 0x00000000;  // 41 - O - Customer OTP 5
  emul->otp.otp_memory[0x2a] = 0x00000000;  // 42 - O - Customer OTP 6
  emul->otp.otp_memory[0x2b] = 0x00000000;  // 43 - O - Customer OTP 7
  emul->otp.otp_memory[0x2d] = 0x00000000;  // 45 - O - License Key 0
  emul->otp.otp_memory[0x2e] = 0x00000000;  // 46 - O - License Key 1
  emul->otp.otp_memory[0x40] = 0x00000000;  // 64 - O - MAC Address Bytes 4 & %
  emul->otp.otp_memory[0x41] = 0x00000000;  // 65 - O - MAC Addrss Bytes 0-3
  emul->otp.otp_memory[0x42] = 0x00000000;  // 66 - O - Advanced Boot Register
  emul->otp.awake = false;
}

uint32_t
otp_load (struct bcm2835_emul *emul, uint32_t address) {
  uint32_t work = address;

  work &= 0x000000FF;
  work /= 4;
  print_log ("otp_load address: %08x\n", address);

  if (work > 9) {
    assert (0 && "Unknown OTP Register!\n");
  }
  if (work == 4) {              // Status register
    return 0x00000001;
  }
  if (work == 6) {
    print_log ("ADDR was: %d\n", emul->otp.registers[7]);
    print_log ("DATA Requested!\n");
    // TODO: Is this correct?
    return emul->otp.otp_memory[emul->otp.registers[7]];
  }
  print_log ("Requested address: 0x%08x, What we got: 0x%08x\n", work,
             emul->otp.registers[work]);
  return emul->otp.registers[work];
}

void
otp_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  uint32_t work = address;

  work &= 0x000000FF;
  work /= 4;

  print_log ("otp_store address: 0x%08x, value: 0x%08x\n", address, value);
  if (work > 9) {
    assert (0 && "Unknown OTP Register!\n");
  }

/*  
  if (address == VC_OTP0_OTP_BOOTMODE_REG) {
    print_log("BOOTMODE -> 0x%08X\n", value);
  } else if (address == VC_OTP0_OTP_CONFIG_REG) {
    print_log("control -> 0x%08X\n", value);
  } else if (address == VC_OTP0_OTP_CTRL_LOW_REG) {
    print_log("control low -> 0x%08X\n", value);
  } else if (address == VC_OTP0_OTP_CTRL_HIGH_REG) {
    print_log("control high -> 0x%08X\n", value);
  } else if (address == VC_OTP0_OTP_STATUS_REG) {
    print_log("status -> 0x%08X\n", value);
  } else if (address == VC_OTP0_OTP_BITSEL_REG) {
    print_log("bitsel -> 0x%08X\n", value);
  } else if (address == VC_OTP0_OTP_DATA_REG) {
    print_log("data -> 0x%08X\n", value);
  } else if (address == VC_OTP0_OTP_ADDR_REG) {
    print_log("addr -> 0x%08X\n", value);
    emul->otp.registers[6] = emul->otp.otp_memory[value];
  } else if (address == VC_OTP0_OTP_WRITE_DATA_READ_REG) {
    print_log("write data read -> 0x%08X\n", value);
  } else if (address == VC_OTP0_OTP_INIT_STATUS_REG) {
    print_log("init status -> 0x%08X\n", value);
  }
*/
  emul->otp.registers[work] = value;
}
