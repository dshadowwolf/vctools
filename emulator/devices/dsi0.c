
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
dsi0_init (struct bcm2835_emul *emul) {
  memset (&emul->dsi0, 0, sizeof (emul->dsi0));
}

uint32_t
dsi0_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log("DSI0 Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
dsi0_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log("DSI0 Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
