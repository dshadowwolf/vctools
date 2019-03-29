
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);
void
timer_init (struct bcm2835_emul *emul) {
  memset (&emul->timer, 0, sizeof (emul->timer));
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
    print_log ("TIMER Address load: 0x%08x\n", address);
  }
  return 0;
  (void) emul;
}

void
timer_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  /*
   * TODO 
   */
  print_log ("Timer Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
