
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
emmc_init (struct bcm2835_emul *emul) {
  memset (&emul->emmc, 0, sizeof (emul->emmc));
}

uint32_t
emmc_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log("EMMC Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
emmc_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log("EMMC Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
