CC = gcc
CXX = g++
PYTHON = python
CFLAGS = -g -Wall -Wextra -Werror
CPPFLAGS = -g -Wall -Wextra -Werror

all: dump_decoder trace_decoder

dump_decoder: vcdecoder.o
	$(CXX) dump_decoder.cpp vcdecoder.o -o dump_decoder $(CPPFLAGS)

trace_decoder: vcdecoder.o
	$(CXX) trace_decoder.cpp vcdecoder.o -o trace_decoder $(CPPFLAGS)

vcdecoder.o: vcdecoder.c
	$(CC) vcdecoder.c -c -o vcdecoder.o $(CFLAGS)

vcdecoder.c:
	$(PYTHON) ../dbscripts/headergen.py --decoder ../vcdb .

clean:
	-rm -f dump_decoder trace_decoder
	-rm -f *.o
	-rm -f vcdecoder.c vcregs.h

