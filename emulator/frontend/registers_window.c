#include <ncurses.h>
#include <stdio.h>
#include "fe_data.h"
#include "../bcm2835_emul.h"
#include "../vc4_emul.h"

static WINDOW *mywin;
static struct bcm2835_emul *emul_copy;

void
updateRegisterWindow (  ) {
  for ( int i = 0; i < 32; i++ ) {
    wattron ( mywin, REGDISP );
    mvwprintw ( mywin, i + 2, 2, "r%02d", i );
    wattroff ( mywin, COLOR_PAIR ( BASE_GREEN ) );
    mvwprintw ( mywin, i + 2, 5, ":" );
    wattroff ( mywin, A_BOLD );
    mvwprintw ( mywin, i + 2, 7, "0x%08X",
                vc4_emul_get_scalar_reg ( emul_copy->vc4, i ) );
  }
  wattron ( mywin, TITLE );
  mvwprintw ( mywin, 1, 5, "REGISTERS" );
  wattroff ( mywin, TITLE );
  box ( mywin, ACS_VLINE, ACS_HLINE );
  wrefresh ( mywin );
}

void
initRegisterWindow ( struct bcm2835_emul *emu ) {
  emul_copy = emu;
  mywin = newwin ( 35, 19, 0, 0 );
  box ( mywin, ACS_VLINE, ACS_HLINE );
  wattron ( mywin, A_BOLD | COLOR_PAIR ( BLUE_HIGH ) );
  mvwprintw ( mywin, 1, 5, "REGISTERS" );
  wattroff ( mywin, A_BOLD | COLOR_PAIR ( BLUE_HIGH ) );
  updateRegisterWindow (  );
  refresh (  );
  wrefresh ( mywin );
}
