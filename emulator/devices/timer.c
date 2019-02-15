
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>

extern void print_log (const char *fmt, ...);
void
timer_init (struct bcm2835_emul *emul) {
  /*
   * TODO 
   */

  (void) emul;
}

uint32_t
timer_load (struct bcm2835_emul *emul, uint32_t address) {
  /*
   * TODO 
   */
  if (address == VC_TIMER_CLO) {
    return 0;
    print_log ("Timer Free Running counter low requested\n");
  } else {
    print_log ("TIMER Address: 0x%08x\n", address);
    assert (0 && "TIMER Not implemented!\n");
  }
  return 0;
  (void) emul;
  (void) address;
}

void
timer_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  /*
   * TODO 
   */
  print_log ("Address: 0x%08x 0x%08x\n", address, value);
  assert (0 && "TIMER Not implemented!\n");
  (void) emul;
  (void) address;
  (void) value;
}
