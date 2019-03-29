AS = vc4-elf-as
LD = vc4-elf-ld
OBJCOPY = vc4-elf-objcopy
PYTHON = python

all: bin/bootloader.bin bin/tracer.bin

clean:
	-rm -rf bin obj vcregs.inc vcregs.h

vcregs.inc: ../vcdb/*.yaml
	$(PYTHON) ../dbscripts/headergen.py --asm ../vcdb .

obj/%.o: %.s vcregs.inc
	@mkdir -p obj
	$(AS) $< -o $@

# bootloader

obj/draminit_include.o: obj/draminit.bin
	$(OBJCOPY) -F elf32-vc4 -B vc4 -I binary $^ $@

bin/bootloader.bin: obj/bootloader.o obj/draminit_include.o
	@mkdir -p bin
	$(LD) -T bootloader.ld -o $@ $^

# draminit

obj/draminit.bin: obj/draminit.o
	@mkdir -p bin
	$(LD) -T program.ld -o $@ $^

# tracer

bin/tracer.bin: obj/tracer.o
	@mkdir -p bin
	$(LD) -T program.ld -o $@ $^

obj/tracer.o: tracer_scalar16.s tracer_scalar32.s tracer_scalar48.s tracer_load_store_emul.s

