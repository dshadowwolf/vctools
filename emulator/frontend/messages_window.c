#include <ncurses.h>
#include <stdio.h>
#include <cdk_test.h>
#include "fe_data.h"
#include "../bcm2835_emul.h"
#include "../vc4_emul.h"

static WINDOW *mywin;
static struct bcm2835_emul *emul_copy;
static CDKSWINDOW *scroller;
static CDKSCREEN *screen;
static FILE *logfile;
static const char* buff[1024];
static unsigned int mark = 0;

const int HEIGHT = 30;

void cleanup() {
  if(logfile) fclose(logfile);
}

void print_log(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  char target[8192];
  vsnprintf(target, 8192, fmt, args);
  va_end(args);

  if(scroller == NULL) {
    buff[mark++] = strdup(target);
    return;
  } else if(mark > 0) {
    for(unsigned int i = 0; i < mark; i++) {
      addCDKSwindow(scroller, buff[i], BOTTOM);
    }
    mark = 0;
  }
  
  addCDKSwindow(scroller, target, BOTTOM);
  fputs(target, logfile);
  fsync(fileno(logfile));  
  //  box(mywin, ACS_VLINE, ACS_HLINE);
  wrefresh(mywin);
}

void initMessagesWindow(struct bcm2835_emul *emu, const char *filename) {
  logfile = fopen(filename, "w");
  emul_copy = emu;
  mywin = newwin(HEIGHT, 133, 35, 0);
  screen = initCDKScreen(mywin);
  
  box(mywin, ACS_VLINE, ACS_HLINE);
  scroller = newCDKSwindow(screen, 36, 1, HEIGHT + 2, 131, NULL, 512, FALSE, FALSE);
  drawCDKSwindow (scroller, ObjOf (scroller)->box);
  refresh();
  wrefresh(mywin);
  atexit(cleanup);
}

void commandMSG(int key) {
  injectCDKSwindow(scroller, key);
}
