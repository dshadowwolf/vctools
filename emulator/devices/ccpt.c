
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
ccpt_init (struct bcm2835_emul *emul) {
  memset (&emul->ccpt, 0, sizeof (emul->ccpt));
}

uint32_t
ccpt_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log("CCPT Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
ccpt_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log("CCPT Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
