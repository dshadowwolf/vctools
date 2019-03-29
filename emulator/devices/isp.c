
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
isp_init (struct bcm2835_emul *emul) {
  memset (&emul->isp, 0, sizeof (emul->isp));
}

uint32_t
isp_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log ("ISP Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
isp_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log ("ISP Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
