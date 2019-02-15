
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

#define VC_A2W_XOSC_CTRL 0x7e102190u
#define VC_A2W_PLLD_PER  0x7e102540u

extern void print_log(const char *fmt, ...);

void a2w_init(struct bcm2835_emul *emul) {
	memset(&emul->a2w, 0, sizeof(emul->a2w));
}
uint32_t a2w_load(struct bcm2835_emul *emul, uint32_t address) {
	if (address == VC_A2W_PLLC_ANA0) {
	} else if (address == VC_A2W_PLLC_ANA1) {
	} else if (address == VC_A2W_PLLC_ANA2) {
	} else if (address == VC_A2W_PLLC_ANA3) {
	} else if (address == VC_A2W_PLLD_ANA0) {
	} else if (address == VC_A2W_PLLD_ANA1) {
	} else if (address == VC_A2W_PLLD_ANA2) {
	} else if (address == VC_A2W_PLLD_ANA3) {
	} else if (address == VC_A2W_PLLC_MULT2) {
	} else if (address == VC_A2W_PLLD_MULT2) {
	} else if (address == VC_A2W_XOSC_CTRL) {
	} else {
		print_log("A2W Load Address: 0x%08x\n", address);
		assert(0 && "Unknown A2W register!\n");
	}
	return 0;
	(void)emul;
	(void)address;
}
void a2w_store(struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
	if (address == VC_A2W_PLLC_DIG0) {
	} else if (address == VC_A2W_PLLC_DIG0) {
	} else if (address == VC_A2W_PLLC_DIG1) {
	} else if (address == VC_A2W_PLLC_DIG2) {
	} else if (address == VC_A2W_PLLC_DIG3) {
	} else if (address == VC_A2W_PLLC_ANA0) {
	} else if (address == VC_A2W_PLLC_ANA1) {
	} else if (address == VC_A2W_PLLC_ANA2) {
	} else if (address == VC_A2W_PLLC_ANA3) {
	} else if (address == VC_A2W_PLLC_MULT2) {
	} else if (address == VC_A2W_PLLD_MULT2) {
	} else if (address == VC_A2W_XOSC_CTRL) {
	} else if (address == VC_A2W_PLLC_MULT_FRACT) {
	} else if (address == VC_A2W_PLLD_MULT_FRACT) {
	} else if (address == VC_A2W_PLLD_PER) {
	} else if (address == VC_A2W_PLLx_DIV) {
	} else {
		print_log("A2W Store Address: 0x%08x, 0x%08x\n", address, value);
		assert(0 && "Unknown A2W register!\n");
	}
	return;
	(void)emul;
	(void)address;
	(void)value;
}

