
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
l1cc_init (struct bcm2835_emul *emul) {
  memset (&emul->l1cc, 0, sizeof (emul->l1cc));
}

uint32_t
l1cc_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log ("L1CC Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
l1cc_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log ("L1CC Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
