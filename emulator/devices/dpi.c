
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
dpi_init (struct bcm2835_emul *emul) {
  memset (&emul->dpi, 0, sizeof (emul->dpi));
}

uint32_t
dpi_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log("DPI Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
dpi_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log("DPI Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
