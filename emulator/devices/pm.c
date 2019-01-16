
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

void pm_init(struct bcm2835_emul *emul) {
	memset(&emul->pm, 0, sizeof(emul->pm));
}
uint32_t pm_load(struct bcm2835_emul *emul, uint32_t address) {
	assert(0 && "Unknown PM register!\n");
	(void)emul;
	(void)address;
}
void pm_store(struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
	assert(0 && "Unknown PM register!\n");
	(void)emul;
	(void)address;
	(void)value;
}

