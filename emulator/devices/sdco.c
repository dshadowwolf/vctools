
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log ( const char *fmt, ... );

void
sdco_init ( struct bcm2835_emul *emul ) {
  memset ( &emul->sdco, 0, sizeof ( emul->sdco ) );
}

uint32_t
sdco_load ( struct bcm2835_emul *emul, uint32_t address ) {
  if ( address == VC_SDCO_CS ) {
    return 0;
  }
  print_log ( "SDCO Address load: %08x\n", address );
  assert ( 0 && "Unknown SDCO register!\n" );
  ( void ) emul;
  ( void ) address;
  return 0;
}

void
sdco_store ( struct bcm2835_emul *emul, uint32_t address, uint32_t value ) {
  print_log ( "SDCO Address store: 0x%08x 0x%08x\n", address, value );
  assert ( 0 && "Unknown SDCO register!\n" );
  ( void ) emul;
  ( void ) address;
  ( void ) value;
}
