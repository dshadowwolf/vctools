
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
jpeg_init (struct bcm2835_emul *emul) {
  memset (&emul->jpeg, 0, sizeof (emul->jpeg));
}

uint32_t
jpeg_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log ("JPEG Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
jpeg_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log ("JPEG Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
