
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
hd_init (struct bcm2835_emul *emul) {
  memset (&emul->hd, 0, sizeof (emul->hd));
}

uint32_t
hd_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log ("HD Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
hd_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log ("HD Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
