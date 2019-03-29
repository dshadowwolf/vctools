
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
vec_init (struct bcm2835_emul *emul) {
  memset (&emul->vec, 0, sizeof (emul->vec));
}

uint32_t
vec_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log ("VEC Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
vec_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log ("VEC Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
