
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
armcb_init (struct bcm2835_emul *emul) {
  memset (&emul->armcb, 0, sizeof (emul->armcb));
}

uint32_t
armcb_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log("ARMCB Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
armcb_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log("ARMCB Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
