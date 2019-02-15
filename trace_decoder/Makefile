CFLAGS = -g -Wall -Wextra
CPPFLAGS = -g -Wall -Wextra

all: dump_decoder trace_decoder

dump_decoder: vcdecoder.o
	g++ dump_decoder.cpp vcdecoder.o -o dump_decoder $(CPPFLAGS)

trace_decoder: vcdecoder.o
	g++ trace_decoder.cpp vcdecoder.o -o trace_decoder $(CPPFLAGS)

vcdecoder.o: vcdecoder.c
	gcc vcdecoder.c -c -o vcdecoder.o $(CFLAGS)

vcdecoder.c:
	python ../dbscripts/headergen.py --decoder ../vcdb .

clean:
	-rm -f dump_decoder trace_decoder
	-rm -f *.o
	-rm -f vcdecoder.c vcregs.h

