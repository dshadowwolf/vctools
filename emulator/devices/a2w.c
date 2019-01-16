
#include "../bcm2835_emul.h"
#include "../vcregs.h"

#include <assert.h>
#include <string.h>

void a2w_init(struct bcm2835_emul *emul) {
	memset(&emul->a2w, 0, sizeof(emul->a2w));
}
uint32_t a2w_load(struct bcm2835_emul *emul, uint32_t address) {
	assert(0 && "Unknown A2W register!\n");
}
void a2w_store(struct bcm2835_emul *emul, uint32_t address, uint32_t value) {
	assert(0 && "Unknown A2W register!\n");
}

