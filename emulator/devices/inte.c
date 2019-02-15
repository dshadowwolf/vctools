
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

void print_log (const char *fmt, ...);

void
inte_init (struct bcm2835_emul *emul) {
  memset (&emul->inte, 0, sizeof (emul->inte));
}

uint32_t
inte_load (struct bcm2835_emul *emul, uint32_t address) {
  /*
   * TODO 
   */
  if (address == VC_INTE_UNK_0x800) {
    return 0;
  }
  print_log ("INTE Address: %08x\n", address);
  assert (0 && "INTE Not implemented!\n");
  (void) emul;
  (void) address;
}

void
inte_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  if (address == VC_INTE_TABLE_PTR) {
    print_log ("INTE ivt %08x\n", value);
    emul->inte.ivt_address = value;
  } else if (address == VC_INTE_UNK_0x800) {
    return;
  } else {
    /*
     * TODO 
     */
    print_log ("INTE Store Address: %08x, Value: %08x\n", address, value);
    assert (0 && "INTE Not implemented!\n");
  }
}

uint32_t
vc4_emul_get_ivt_address (void *user_data) {
  struct bcm2835_emul *emul = user_data;

  return emul->inte.ivt_address;
}
