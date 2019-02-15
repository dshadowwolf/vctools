
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
void print_log ( const char *fmt, ... );

void
aux_init ( struct bcm2835_emul *emul ) {
  /*
   * TODO 
   */
  ( void ) emul;
}

uint32_t
aux_load ( struct bcm2835_emul *emul, uint32_t address ) {
  if ( address == VC_AUX_MU_LSR_REG ) {
    return 0;                   // FIFO empty, we're idle
  } else {
    print_log ( "AUX load %08x\n", address );
    /*
     * TODO 
     */
    assert ( 0 && "Unknown AUX Register!\n" );
    ( void ) emul;
  }
}

void
aux_store ( struct bcm2835_emul *emul, uint32_t address, uint32_t value ) {
  if ( address == VC_AUX_IRQ ) {
  } else if ( address == VC_AUX_ENABLES ) {
  } else if ( address == VC_AUX_MU_IO_REG ) {
    if ( value >= 32 && value < 127 ) {
      print_log ( "%c", value );
    } else {
      print_log ( "[0x%02x]", value );
    }
  } else if ( address == VC_AUX_MU_IER_REG ) {
  } else if ( address == VC_AUX_MU_IIR_REG ) {
  } else if ( address == VC_AUX_MU_LCR_REG ) {
  } else if ( address == VC_AUX_MU_MCR_REG ) {
  } else if ( address == VC_AUX_MU_LSR_REG ) {
  } else if ( address == VC_AUX_MU_SR_REG ) {
  } else if ( address == VC_AUX_MU_SCRATCH ) {
  } else if ( address == VC_AUX_MU_CNTL_REG ) {
  } else if ( address == VC_AUX_MU_STAT_REG ) {
  } else if ( address == VC_AUX_MU_BAUD_REG ) {
  } else {
    /*
     * TODO 
     */
    print_log ( "AUX Store Address: 0x%08x, 0x%08x", address, value );
    assert ( 0 && "Unknown AUX Register!\n" );
    ( void ) emul;
  }
}
