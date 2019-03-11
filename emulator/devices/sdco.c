
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
sdco_init (struct bcm2835_emul *emul) {
  memset (&emul->sdco, 0, sizeof (emul->sdco));
}

uint32_t
sdco_load (struct bcm2835_emul *emul, uint32_t address) {
  if (address == VC_SDCO_CS) {
    if (emul->sdco.cs & 0x00000008) {
      return 0x00000000;
    } else {
      return 0x00008000;
    }
  } else if (address == VC_SDCO_MR) {
    return 0x80000000;
  }
  print_log ("SDCO Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
sdco_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  if (address == VC_SDCO_CS) {
    emul->sdco.cs = value;
    return;
  } else if (address == VC_SDCO_SA) {
    emul->sdco.sa = value;
    return;
  } else if (address == VC_SDCO_SB) {
    emul->sdco.sb = value;
    return;
  } else if (address == VC_SDCO_SC) {
    emul->sdco.sc = value;
    return;
  } else if (address == VC_SDCO_PT2) {
    emul->sdco.pt2 = value;
    return;
  } else if (address == VC_SDCO_PT1) {
    emul->sdco.pt1 = value;
    return;
  } else if (address == VC_SDCO_MR) {
    emul->sdco.mr = value;
    return;
  } else if (address == VC_SDCO_SD) {
    emul->sdco.sd = value;
    return;
  } else if (address == VC_SDCO_SE) {
    emul->sdco.se = value;
    return;
  }
  print_log ("SDCO Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
