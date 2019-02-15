
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
void print_log(const char *fmt, ...);

void aux_init(struct bcm2835_emul *emul) {
	/* TODO */
	(void)emul;
}
uint32_t aux_load(struct bcm2835_emul *emul, uint32_t address) {
	if (address == VC_AUX_MU_LSR_REG) {
		return VC_AUX_MU_LSR_REG_TX_IDLE | VC_AUX_MU_LSR_REG_TX_EMPTY;
	} else {
		print_log("AUX load %08x\n", address);
		/* TODO */
		assert(0 && "Not implemented!\n");
		(void)emul;
	}
}
void aux_store(struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
	if (address == VC_AUX_IRQ) {
	} else if (address == VC_AUX_ENABLES) {
	} else if (address == VC_AUX_MU_IO_REG) {
		if (isprint(value & 0xff)) {
			print_log("UART \'%c\'\n", value & 0xff);
		} else {
			print_log("UART 0x%02x\n", value & 0xff);
		}
	} else if (address == VC_AUX_MU_IER_REG) {
	} else if (address == VC_AUX_MU_IIR_REG) {
	} else if (address == VC_AUX_MU_LCR_REG) {
	} else if (address == VC_AUX_MU_MCR_REG) {
	} else if (address == VC_AUX_MU_LSR_REG) {
	} else if (address == VC_AUX_MU_SR_REG) {
	} else if (address == VC_AUX_MU_SCRATCH) {
	} else if (address == VC_AUX_MU_CNTL_REG) {
	} else if (address == VC_AUX_MU_STAT_REG) {
	} else if (address == VC_AUX_MU_BAUD_REG) {
	} else {
		/* TODO */
		print_log("AUX store %x, %x", address, value);
		//assert(0 && "Not implemented!\n");
		(void)emul;
	}
}

