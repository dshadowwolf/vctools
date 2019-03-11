
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
pm_init (struct bcm2835_emul *emul) {
  memset (&emul->pm, 0, sizeof (emul->pm));
}

uint32_t
pm_load (struct bcm2835_emul *emul, uint32_t address) {
  if (address == VC_PM_IMAGE) {
    return 0x00000012;
    return emul->pm.image;
  }
  print_log("PM Address load: 0x%08x\n", address);
  return 0;
}

void
pm_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  if (address == VC_PM_IMAGE) {
    emul->pm.image = value;
   return; 
  }
  print_log("PM Address store: 0x%08x 0x%08x\n", address, value);
}
