
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
void print_log (const char *fmt, ...);

void
aux_init (struct bcm2835_emul *emul) {
  memset (&emul->aux, 0, sizeof (emul->aux));
}

uint32_t
aux_load (struct bcm2835_emul *emul, uint32_t address) {
  if (address == VC_AUX_MU_LSR_REG) {
    // FIFO empty, we're idle
    return 0x20;
  } else {
    print_log ("AUX load %08x\n", address);
  }
  return 0;
  (void) emul;
}

void
aux_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  if (address == VC_AUX_IRQ) {
  } else if (address == VC_AUX_ENABLES) {
  } else if (address == VC_AUX_MU_IO_REG) {
    if (value >= 32 && value < 127) {
      print_log ("%c", value);
    } else {
      print_log ("[0x%02x]", value);
    }
  } else if (address == VC_AUX_MU_IER_REG) {
  } else if (address == VC_AUX_MU_IIR_REG) {
  } else if (address == VC_AUX_MU_LCR_REG) {
  } else if (address == VC_AUX_MU_MCR_REG) {
  } else if (address == VC_AUX_MU_LSR_REG) {
  } else if (address == VC_AUX_MU_SR_REG) {
  } else if (address == VC_AUX_MU_SCRATCH) {
  } else if (address == VC_AUX_MU_CNTL_REG) {
  } else if (address == VC_AUX_MU_STAT_REG) {
  } else if (address == VC_AUX_MU_BAUD_REG) {
  } else {
    /*
     * TODO 
     */
    print_log ("AUX Store Address: 0x%08x, 0x%08x", address, value);
    (void) emul;
  }
}
