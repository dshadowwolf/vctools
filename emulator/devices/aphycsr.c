
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
aphycsr_init (struct bcm2835_emul *emul) {
  memset (&emul->aphycsr, 0, sizeof (emul->aphycsr));
}

uint32_t
aphycsr_load (struct bcm2835_emul *emul, uint32_t address) {
  if (address == VC_APHYCSR_GLBL_ADR_DLL_LOCK_STAT) {
    return 0x00000003;
  } else if (address == VC_APHYCSR_DDR_PLL_GLOBAL_RESET) {
    return 0x00000000;
  } else if (address == VC_APHYCSR_DDR_PLL_LOCK_STATUS) {
    return emul->aphycsr.ddr_pll_lock_status;
  } else if (address == VC_APHYCSR_ADDR_PVT_COMP_STATUS) {
    return 0x00000002;
  }
  print_log ("APHYCSR Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
aphycsr_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  if (address == VC_APHYCSR_DDR_PLL_GLOBAL_RESET) {
    emul->aphycsr.ddr_pll_lock_status = 0x00010000;
  }
  print_log ("APHYCSR Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
