
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
dma_init (struct bcm2835_emul *emul) {
  memset (&emul->dma, 0, sizeof (emul->dma));
}

uint32_t
dma_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log ("DMA Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
dma_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log ("DMA Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
