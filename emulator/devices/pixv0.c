
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
pixv0_init (struct bcm2835_emul *emul) {
  memset (&emul->pixv0, 0, sizeof (emul->pixv0));
}

uint32_t
pixv0_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log ("PIXV0 Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
pixv0_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log ("PIXV0 Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
