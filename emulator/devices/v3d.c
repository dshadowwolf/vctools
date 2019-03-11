
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
v3d_init (struct bcm2835_emul *emul) {
  memset (&emul->v3d, 0, sizeof (emul->v3d));
}

uint32_t
v3d_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log("V3D Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
v3d_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log("V3D Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
