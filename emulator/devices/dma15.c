
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
dma15_init (struct bcm2835_emul *emul) {
  memset (&emul->dma15, 0, sizeof (emul->dma15));
}

uint32_t
dma15_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log("DMA15 Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
dma15_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log("DMA15 Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
