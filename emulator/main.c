
#include "bcm2835_emul.h"
#include "vc4_emul.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include <ncurses.h>

extern void initRegisterWindow(struct bcm2835_emul *emul);
extern void updateRegisterWindow();
extern void initMemoryWindow(struct bcm2835_emul *emul, char w);
extern void updateMemoryWindow();
extern void initStackWindow(struct bcm2835_emul *emul);
extern void updateStackWindow();
extern void initMessagesWindow(struct bcm2835_emul *emul, const char *fileName);
extern void commandMSG(int key);
extern void memScrollUp();
extern void memScrollDown();
extern void print_log(const char *fmt, ...);

int load_file(struct bcm2835_emul *emul,
              const char *filename,
              uint32_t target_address) {
	char buffer[512];
	size_t length;
	FILE *file = fopen(filename, "rb");
	if (file == NULL) {
		return -1;
	}
	do {
		length = fread(buffer, 1, 512, file);
		memory_fill(emul, target_address, buffer, length);
		target_address += 512;
	} while (length == 512);
	return 0;
}

const char *help = "Usage:\n\
    %s <options>\n\
Where <options> can contain the following:\n\
    -h          Prints this help.\n\
    -c IMAGE    Specifies the SD card image to be used.\n\
    -s PORT     Creates a local TCP server at PORT for uart data.\n\
    -r ROMFILE  Specifies a bootrom file which is placed at 0x60000000.\n\
    -b BOOTCODE Specifies a bootcode.bin file which is placed at 0x80000000.\n\
At least either bootrom or bootcode.bin is necessary.\n\
If a bootcode.bin file is specified, execution starts with this file. \
If not bootcode.bin file is present, the bootrom is used to load it from the \
SD card image.\n";

int main(int argc, char **argv) {
	int option;
	int i;

	const char *sdcard_file = NULL;
	const char *rom_file = NULL;
	const char *bootcode_file = NULL;
	char *log_file = NULL;
	
	int serial_port = -1;

	/* parse the command line arguments */
	while ((option = getopt(argc, argv, "c:s:r:b:hl:")) != -1) {
		switch (option) {
			case 'h':
				printf(help, argv[0]);
				return 0;
			case 'c':
				sdcard_file = optarg;
				break;
			case 's':
				serial_port = atoi(optarg);
				break;
			case 'r':
				rom_file = optarg;
				break;
			case 'b':
				bootcode_file = optarg;
				break;
		        case 'l':
			        log_file = optarg;
			        break;
			case '?':
				if (strchr("csrbh", optopt) != NULL) {
					fprintf(stderr, "Option -%c requires an argument.\n",
					        optopt);
				} else if (isprint(optopt)) {
					fprintf (stderr, "Unknown option \'-%c\'.\n", optopt);
				} else {
					fprintf (stderr, "Unknown option character \'\\x%x\'.\n",
					         optopt);
				}
				return -1;
			default:
				abort();
		}
	}
	if (optind != argc) {
		for (i = optind; i < argc; i++) {
			fprintf(stderr, "Error: Invalid argument %s\n", argv[i]);
		}
		printf(help, argv[0]);
		return -1;
	}
	if (rom_file == NULL && bootcode_file == NULL) {
		fprintf(stderr, "Error: Cannot boot without bootrom or bootcode.\n");
		printf(help, argv[0]);
		return -1;
	}
	
	/* create the emulator */
	struct bcm2835_emul *emul = calloc(1, sizeof(struct bcm2835_emul));
	emul->vc4 = vc4_emul_init(emul);
	memory_init(emul);
	if (mmc_init(emul, sdcard_file) != 0) {
		fprintf(stderr, "Error: Cannot initialize MMC.\n");
		return -1;
	}
	aux_init(emul);
	otp_init(emul);
	gpio_init(emul);
	timer_init(emul);
	cm_init(emul);
	a2w_init(emul);
	inte_init(emul);
	/* load the boot code into memory */
	if (rom_file != NULL) {
		if (load_file(emul, rom_file, BOOTROM_BASE_ADDRESS) != 0) {
			fprintf(stderr, "Could not open the bootrom file!\n");
			return -1;
		}
		vc4_emul_set_scalar_reg(emul->vc4, 31, BOOTROM_BASE_ADDRESS);
	}
	if (bootcode_file != NULL) {
		if (load_file(emul, bootcode_file, DRAM_BASE_ADDRESS) != 0) {
			fprintf(stderr, "Could not open the bootcode file!\n");
			return -1;
		}
		vc4_emul_set_scalar_reg(emul->vc4, 31, DRAM_BASE_ADDRESS);
	}
	if(log_file == NULL) {
	  log_file = malloc(sizeof(char) * (strlen(bootcode_file)+9));
	  memset(log_file, 0, sizeof(char) * (strlen(bootcode_file)+9));
	  sprintf(log_file, "%s.log.txt", bootcode_file);
	}
	/* start the emulator */
	/* TODO */
	int paused = 0, step = 0;
	    initscr();
  start_color();
  init_pair(0, COLOR_WHITE, COLOR_BLACK);
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_WHITE, COLOR_BLUE);
  init_pair(4, COLOR_BLACK, COLOR_RED);
  
  cbreak();
  keypad(stdscr, TRUE);         /* I need that nifty F1         */
  noecho();
  int base_state = curs_set(0);
  timeout(0);
  initRegisterWindow(emul);
  initMemoryWindow(emul, 'r');
  initStackWindow(emul);
  initMessagesWindow(emul, log_file);
	for (;;) {
	  //		printf("step: %08x\n", vc4_emul_get_scalar_reg(emul->vc4, 31));
	  if(paused==0 && step == 0) {
		vc4_emul_step(emul->vc4);
	  }
		updateRegisterWindow();
		updateMemoryWindow();
		updateStackWindow();
		refresh();

		int key = getch();
		switch( key ) {
		case KEY_F(1):
		  goto exit;
		case KEY_F(2):
		  if(paused) {
		    paused = 0;
		    timeout(0);
		  } else {
		    paused = 1;
		    timeout(-1);
		  }
		  break;
		case KEY_F(3):
		  if(step == 0) step = 1;
		  else step = 0;
		  break;
		case KEY_F(4):
		  if(paused == 0 && step) vc4_emul_step(emul->vc4);
		  break;
		case KEY_F(5):
		  print_log("RESET for single-step!\n");
		  step = 1;
		  emul->vc4 = vc4_emul_init(emul);
		  memory_init(emul);
		  if (mmc_init(emul, sdcard_file) != 0) {
		    print_log("Error: Cannot initialize MMC.\n");
		    return -1;
		  }
		  aux_init(emul);
		  otp_init(emul);
		  gpio_init(emul);
		  timer_init(emul);
		  cm_init(emul);
		  a2w_init(emul);
		  inte_init(emul);
		  /* load the boot code into memory */
		  if (rom_file != NULL) {
		    if (load_file(emul, rom_file, BOOTROM_BASE_ADDRESS) != 0) {
		      print_log("Could not open the bootrom file!\n");
		      return -1;
		    }
		    vc4_emul_set_scalar_reg(emul->vc4, 31, BOOTROM_BASE_ADDRESS);
		  }
		  if (bootcode_file != NULL) {
		    if (load_file(emul, bootcode_file, DRAM_BASE_ADDRESS) != 0) {
		      print_log("Could not open the bootcode file!\n");
		      return -1;
		    }
		    vc4_emul_set_scalar_reg(emul->vc4, 31, DRAM_BASE_ADDRESS);
		  }
		  updateRegisterWindow();
		  updateMemoryWindow();
		  updateStackWindow();
		  refresh();
		  break;
		case KEY_F(6):
		  print_log("RESET - machine paused, press F2 to unpause\n");
		  paused = 1;
		  timeout(-1);
		  emul->vc4 = vc4_emul_init(emul);
		  memory_init(emul);
		  if (mmc_init(emul, sdcard_file) != 0) {
		    print_log("Error: Cannot initialize MMC.\n");
		    return -1;
		  }
		  aux_init(emul);
		  otp_init(emul);
		  gpio_init(emul);
		  timer_init(emul);
		  cm_init(emul);
		  a2w_init(emul);
		  inte_init(emul);
		  /* load the boot code into memory */
		  if (rom_file != NULL) {
		    if (load_file(emul, rom_file, BOOTROM_BASE_ADDRESS) != 0) {
		      print_log("Could not open the bootrom file!\n");
		      return -1;
		    }
		    vc4_emul_set_scalar_reg(emul->vc4, 31, BOOTROM_BASE_ADDRESS);
		  }
		  if (bootcode_file != NULL) {
		    if (load_file(emul, bootcode_file, DRAM_BASE_ADDRESS) != 0) {
		      print_log("Could not open the bootcode file!\n");
		      return -1;
		    }
		    vc4_emul_set_scalar_reg(emul->vc4, 31, DRAM_BASE_ADDRESS);
		  }
		  updateRegisterWindow();
		  updateMemoryWindow();
		  updateStackWindow();
		  refresh();
		  break;
		case KEY_PPAGE:
		  memScrollDown();
		  break;
		case KEY_NPAGE:
		  memScrollUp();
		  break;
		case KEY_UP:
		case KEY_DOWN:
		  commandMSG(key);
		};
		
	}

 exit:
	curs_set(base_state);
	endwin();

	printf("exited with PC: 0x%08X\n", vc4_emul_get_scalar_reg(emul->vc4, 31));
	return 0;
}

