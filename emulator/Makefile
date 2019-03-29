CC = gcc
PYTHON = python
CFLAGS = -g -Wall -Wextra -Werror 
CFLAGS_CDK = -I/usr/include/cdk
CFLAGS_VC4_EMUL = -g -Wall -Wextra -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-sign-compare
LIBS = -lm -lcdk -lncursesw

BOOTMODE = 0x1020000a
CPUID = 0x04000104 # 0x04000104, 0x04000140, 0x04010104, 0x04010140
MEMORY = 512

.NOTPARALLEL: vcregs.h vc4_decoder.c

all: vcregs.h vc4_decoder.c bcm2835_emul

bcm2835_emul: main.o vc4_decoder.o vc4_data.o vc4_emul.o memory.o \
              devices/mult.o devices/ccpt.o devices/inte.o devices/timer.o \
              devices/txp.o devices/jpeg.o devices/mphi.o devices/dma.o \
	      devices/nu.o devices/arba.o devices/brdg.o devices/armcb.o \
              devices/pm.o devices/cm.o devices/a2w.o devices/avs.o devices/rng.o \
	      devices/gpio.o devices/uart.o devices/mmc.o devices/pcm.o \
	      devices/spi0.o devices/bsc0.o devices/pixv0.o devices/pixv1.o \
	      devices/dpi.o devices/dsi0.o devices/tb.o devices/pwm0.o \
	      devices/perm.o devices/tec.o devices/otp.o devices/slim.o \
	      devices/cpg.o devices/ts.o devices/avsp.o devices/i2cspislv.o \
	      devices/aux.o devices/aveout.o devices/emmc.o devices/ddrv.o \
	      devices/smi.o devices/dsi1.o devices/cam0.o devices/cam1.o \
	      devices/cmi.o devices/bsc1.o devices/bsc2.o devices/vec.o \
	      devices/pixv2.o devices/hd.o devices/hdcp.o devices/piarbctl.o \
	      devices/hdmi.o devices/avein.o devices/usb.o devices/isp.o \
	      devices/v3d.o devices/sdco.o devices/l2cc.o devices/l1cc.o \
	      devices/arbr.o devices/dma15.o devices/aphycsr.o devices/dcrc.o \
	      devices/axip.o devices/h264.o devices/vce.o \
	      frontend/registers_window.o frontend/memory_window.o \
	      frontend/stack_window.o frontend/messages_window.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

memory.o: memory.c
	$(CC) -c -o $@ $^ $(CFLAGS) -DMEMORY=$(MEMORY)

vc4_emul.o: vc4_emul.c
	$(CC) -c -o $@ $^ $(CFLAGS_VC4_EMUL) -DCPUID=$(CPUID)

vc4_decoder.o: vc4_decoder.c
	$(CC) -c -o $@ $^ $(CFLAGS_VC4_EMUL) -DCPUID=$(CPUID)

devices/otp.o: devices/otp.c
	$(CC) -c -o $@ $^ $(CFLAGS) -DBOOTMODE=$(BOOTMODE)

frontend/messages_window.o: frontend/messages_window.c
	$(CC) -c -o $@ $^ $(CFLAGS) $(CFLAGS_CDK)

%.o: %.c vc4_emul.h vc4_registers.h vcregs.h bcm2835_emul.h devices/cm.h devices/gpio.h \
     devices/inte.h
	$(CC) -c -o $@ $< $(CFLAGS)

vc4_decoder.c: ../vcdb/_instructions.yaml vcregs.h
	$(PYTHON) ../dbscripts/emulgen.py ../vcdb .

vcregs.h:
	$(PYTHON) ../dbscripts/headergen.py ../vcdb .

clean:
	-rm -f bcm2835_emul
	-rm -f *.o devices/*.o frontend/*.o
	-rm -f vcregs.h vc4_decoder.c

