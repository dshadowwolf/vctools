
#ifndef DEVICES_INTE_H_INCLUDED
#define DEVICES_INTE_H_INCLUDED

/*
7E002000 			
7E002004 			
7E002008 			
7E00200C 			
7E002010 	Priority 	start_cd.elf 	4 bits of priority per interrupt.
7E002014 	Priority 	start_cd.elf 	4 bits of priority per interrupt.
7E002018 	Priority 	start_cd.elf 	4 bits of priority per interrupt.
7E00201C 	Priority 	start_cd.elf 	4 bits of priority per interrupt.
7E002020 			
7E002024 			
7E002028 			
7E00202C 			
7E002030 	Interrupt table address 	loader.bin 	Write the address of the interrupt vector table here to enable interrupts. You should make sure r28 contains a valid stack pointer for interrupt handlers to use before setting this.
7E002034 			
7E002038 			
7E002040 		start_cd 	1 unknown bit of information per interrupt (0-31)
7E002044 		start_cd 	1 unknown bit of information per interrupt (32-63)*/

struct inte_data {
  uint32_t registers[17];
};

#endif
