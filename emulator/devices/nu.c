
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
nu_init (struct bcm2835_emul *emul) {
  memset (&emul->nu, 0, sizeof (emul->nu));
}

uint32_t
nu_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log("NU Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
nu_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log("NU Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
