
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
mult_init (struct bcm2835_emul *emul) {
  memset (&emul->mult, 0, sizeof (emul->mult));
}

uint32_t
mult_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log("MULT Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
mult_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
// 0x7e0000b8
// 0x7e0000bc
  print_log("Mult Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
