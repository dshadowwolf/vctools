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

#define load(x, y) vc4_emul_load(emul_copy->vc4->user_data, (x), (y))
#define GET_BYTE(x) (isprint((x))?x:'.')

static void
print_stackline (unsigned int addr_start, int line) {
  unsigned char data[4];

  for (int i = 0; i < 4; i++) {
    data[i] = (unsigned char) load (addr_start + i, 2);
  }

  wattron (mywin, A_BOLD | COLOR_PAIR (2));
  mvwprintw (mywin, line + 2, 2, "0x%08X:", addr_start);
  wattroff (mywin, COLOR_PAIR (2));
  wattron (mywin, COLOR_PAIR (3));
  mvwprintw (mywin, line + 2, 14, "%02X %02X %02X %02X", data[0x00],
             data[0x01], data[0x02], data[0x03]);
  wattroff (mywin, COLOR_PAIR (3) | A_BOLD);
  mvwprintw (mywin, line + 2, 27, "%c%c%c%c", GET_BYTE (data[0x00]),
             GET_BYTE (data[0x01]), GET_BYTE (data[0x02]),
             GET_BYTE (data[0x03]));
}

void
updateStackWindow () {
  int addrBase = vc4_emul_get_scalar_reg (emul_copy->vc4, 25);

  wattron (mywin, A_BOLD | COLOR_PAIR (BASE_GREEN));
  for (int i = 0; i < 32; i++) {
    print_stackline (addrBase + (4 * i), i);
  }
  box (mywin, ACS_VLINE, ACS_HLINE);
  wattron (mywin, A_BOLD | COLOR_PAIR (BLUE_HIGH));
  mvwprintw (mywin, 1, 12, "STACK");
  wattroff (mywin, A_BOLD | COLOR_PAIR (BLUE_HIGH));
  wrefresh (mywin);
}

void
initStackWindow (struct bcm2835_emul *emu) {
  emul_copy = emu;
  mywin = newwin (35, 33, 0, 100);
  box (mywin, ACS_VLINE, ACS_HLINE);
  wattron (mywin, A_BOLD | COLOR_PAIR (BLUE_HIGH));
  mvwprintw (mywin, 1, 12, "STACK");
  wattroff (mywin, A_BOLD | COLOR_PAIR (BLUE_HIGH));
  updateStackWindow ();
  refresh ();
  wrefresh (mywin);
}
