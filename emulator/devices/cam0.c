
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
cam0_init (struct bcm2835_emul *emul) {
  memset (&emul->cam0, 0, sizeof (emul->cam0));
}

uint32_t
cam0_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log ("CAM0 Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
cam0_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log ("CAM0 Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
