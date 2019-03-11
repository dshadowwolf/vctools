
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log (const char *fmt, ...);

void
i2cspislv_init (struct bcm2835_emul *emul) {
  memset (&emul->i2cspislv, 0, sizeof (emul->i2cspislv));
  (void) emul;
}

uint32_t
i2cspislv_load (struct bcm2835_emul *emul, uint32_t address) {
  print_log ("I2C_SPI_SLV Address load: 0x%08x\n", address);
  return 0;
  (void) emul;
}

void
i2cspislv_store (struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
  print_log ("I2C_SPI_SLV Address store: 0x%08x 0x%08x\n", address, value);
  (void) emul;
}
