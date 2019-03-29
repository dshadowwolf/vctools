
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
dcrc_init (struct bcm2835_emul *emul) {
  memset (&emul->dcrc, 0, sizeof (emul->dcrc));
}

uint32_t
dcrc_load (struct bcm2835_emul *emul, uint32_t address) {
  if (address == VC_DCRC_GLBL_MSTR_DLL_LOCK_STAT) {
    return 0x0000ffff;
  } else if (address == VC_DCRC_DQ_PVT_COMP_STATUS) {
    return 0x00000002;
  }
  print_log ("DCRC Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
dcrc_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log ("DCRC Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
