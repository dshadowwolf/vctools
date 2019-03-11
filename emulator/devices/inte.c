
#include "../bcm2835_emul.h"
#include "../vcregs.h"
 
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_log (const char *fmt, ...);

void
inte_init (struct bcm2835_emul *emul) {
  memset (&emul->inte, 0, sizeof (emul->inte));
}

#define REG(x) (((x) & 0xFF)/4)

uint32_t
inte_load (struct bcm2835_emul *emul, uint32_t address) {
  if (address == VC_INTE_TABLE_PTR && emul->inte.registers[REG(address)] == 0) {
    print_log("Stopping Execution as INTE_TABLE_PTR wasn't set!\n");
    exit(EXIT_FAILURE);
  }
  print_log ("INTE Load Address: %08x [register number: %u]\n", address, REG(address));
  return emul->inte.registers[REG(address)];
}

void
inte_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log ("INTE Store Address: %08x [register number: %u]\n", address, REG(address));
  emul->inte.registers[REG(address)] = value;
}

#undef REG

uint32_t
vc4_emul_get_ivt_address (void *user_data) {
  struct bcm2835_emul *emul = user_data;

  return inte_load(emul, 0x7E002030);
}
