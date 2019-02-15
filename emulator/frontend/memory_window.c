#include <ncurses.h>
#include <stdio.h>
#include <setjmp.h>
#include <ctype.h>
#include "fe_data.h"
#include "../bcm2835_emul.h"
#include "../vc4_emul.h"

struct vc4_emul {
  void *user_data;

  uint32_t scalar_regs[32];
  int pc_changed;

  uint32_t ivt;

  sigjmp_buf exception_handler;
};

static WINDOW *mywin;
static struct bcm2835_emul *emul_copy;
static char which;

#define load(x, y) vc4_emul_load(emul_copy->vc4->user_data, (x), (y))
#define GET_BYTE(x) (isprint((x))?x:'.')

static void
print_memline ( unsigned int addr_start, int line ) {
  unsigned char data[16];

  for ( int i = 0; i < 16; i++ ) {
    data[i] = ( unsigned char ) load ( addr_start + i, 2 );
  }

  wattron ( mywin, A_BOLD | COLOR_PAIR ( 2 ) );
  mvwprintw ( mywin, line + 2, 2, "0x%08X:", addr_start );
  wattroff ( mywin, COLOR_PAIR ( 2 ) );
  wattron ( mywin, COLOR_PAIR ( 3 ) );
  mvwprintw ( mywin, line + 2, 14,
              "%02X %02X %02X %02X %02X %02X %02X %02X  %02X %02X %02X %02X %02X %02X %02X %02X",
              data[0x00], data[0x01], data[0x02], data[0x03], data[0x04],
              data[0x05], data[0x06], data[0x07], data[0x08], data[0x09],
              data[0x0a], data[0x0b], data[0x0c], data[0x0d], data[0x0e],
              data[0x0f] );
  wattroff ( mywin, COLOR_PAIR ( 3 ) );
  wattron ( mywin, COLOR_PAIR ( 2 ) );
  mvwprintw ( mywin, line + 2, 63, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
              GET_BYTE ( data[0x00] ), GET_BYTE ( data[0x01] ),
              GET_BYTE ( data[0x02] ), GET_BYTE ( data[0x03] ),
              GET_BYTE ( data[0x04] ), GET_BYTE ( data[0x05] ),
              GET_BYTE ( data[0x06] ), GET_BYTE ( data[0x07] ),
              GET_BYTE ( data[0x08] ), GET_BYTE ( data[0x09] ),
              GET_BYTE ( data[0x0a] ), GET_BYTE ( data[0x0b] ),
              GET_BYTE ( data[0x0c] ), GET_BYTE ( data[0x0d] ),
              GET_BYTE ( data[0x0e] ), GET_BYTE ( data[0x0f] ) );
  wattroff ( mywin, COLOR_PAIR ( 2 ) | A_BOLD );
}

static int32_t scroll_offset = 0;

void
updateMemoryWindow (  ) {
  int addrBase = vc4_emul_get_scalar_reg ( emul_copy->vc4, 24 );

  addrBase |= 0x0FFF;
  addrBase ^= 0x0FFF;
  addrBase += scroll_offset * 16;

  wattron ( mywin, A_BOLD | COLOR_PAIR ( BASE_GREEN ) );
  for ( int i = 0; i < 32; i++ ) {
    print_memline ( addrBase + ( 16 * i ), i );
  }
  box ( mywin, ACS_VLINE, ACS_HLINE );
  wattron ( mywin, A_BOLD | COLOR_PAIR ( BLUE_HIGH ) );
  mvwprintw ( mywin, 1, 38, "MEMORY" );
  wattroff ( mywin, A_BOLD | COLOR_PAIR ( BLUE_HIGH ) );
  wrefresh ( mywin );
}

void
initMemoryWindow ( struct bcm2835_emul *emu, char w ) {
  which = w;
  emul_copy = emu;
  mywin = newwin ( 35, 81, 0, 19 );
  box ( mywin, ACS_VLINE, ACS_HLINE );
  wattron ( mywin, A_BOLD | COLOR_PAIR ( BLUE_HIGH ) );
  mvwprintw ( mywin, 1, 38, "MEMORY" );
  wattroff ( mywin, A_BOLD | COLOR_PAIR ( BLUE_HIGH ) );
  updateMemoryWindow (  );
  refresh (  );
  wrefresh ( mywin );
}

void
memScrollUp (  ) {
  scroll_offset++;
}

void
memScrollDown (  ) {
  scroll_offset--;
}
