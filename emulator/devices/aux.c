
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>

void aux_init(struct bcm2835_emul *emul) {
	/* TODO */
	(void)emul;
}
uint32_t aux_load(struct bcm2835_emul *emul, uint32_t address) {
	/* TODO */
	assert(0 && "Not implemented!\n");
	(void)emul;
	(void)address;
}
void aux_store(struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
	/* TODO */
	assert(0 && "Not implemented!\n");
	(void)emul;
	(void)address;
	(void)value;
}

