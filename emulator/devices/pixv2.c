
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
pixv2_init (struct bcm2835_emul *emul) {
  memset (&emul->pixv2, 0, sizeof (emul->pixv2));
}

uint32_t
pixv2_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log("PIXV2 Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
pixv2_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log("PIXV2 Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
