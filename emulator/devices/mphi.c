
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
mphi_init (struct bcm2835_emul *emul) {
  memset (&emul->mphi, 0, sizeof (emul->mphi));
  (void) emul;
}

uint32_t
mphi_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log ("MPHI Address load: 0x%08x\n", address);
  return 1;
  (void) emul;
}

void
mphi_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log ("MPHI Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
