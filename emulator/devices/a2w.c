
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

extern void print_log(const char *fmt, ...);

void a2w_init(struct bcm2835_emul *emul) {
	memset(&emul->a2w, 0, sizeof(emul->a2w));
}
uint32_t a2w_load(struct bcm2835_emul *emul, uint32_t address) {
//	if (address == VC_A2W_PLLC_MULT) {
	if (address == VC_A2W_PLLC_UNK_0x30) {
	} else if (address == VC_A2W_PLLC_UNK_0x34) {
	} else if (address == VC_A2W_PLLC_UNK_0x38) {
	} else if (address == VC_A2W_PLLC_UNK_0x3c) {
	} else if (address == VC_A2W_PLLD_UNK_0x50) {
	} else if (address == VC_A2W_PLLD_UNK_0x54) {
	} else if (address == VC_A2W_PLLD_UNK_0x58) {
	} else if (address == VC_A2W_PLLD_UNK_0x5c) {
	} else if (address == VC_A2W_PLLC_MULT2) {
	} else if (address == VC_A2W_PLLD_MULT2) {
	} else if (address == 2114986384) { // 0x7e102190
	} else {
		print_log("Address was: %x (%d)", address, address);
		assert(0 && "Load: Unknown A2W register!\n");
	}
	return 0;
	(void)emul;
	(void)address;
}
void a2w_store(struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
	if (address == VC_A2W_PLLC_MULT) {
	} else if (address == VC_A2W_PLLC_MULT2) {
	} else if (address == VC_A2W_PLLD_MULT2) {
	} else if (address == 2114986384) { // 0x7e102190
	} else if (address == VC_A2W_PLLC_MULT_FRACT) {
	} else if (address == VC_A2W_PLLD_MULT_FRACT) {
	} else if (address == 2114987328) { // 0x7e102540
	} else if (address == VC_A2W_PLLx_DIV) {
	} else {
		print_log("Address was: %x (%d)", address, address);
		assert(0 && "Store: Unknown A2W register!\n");
	}
	return;
	(void)emul;
	(void)address;
	(void)value;
}

