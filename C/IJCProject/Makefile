CC=gcc
CFLAGS= -O2 -std=c99 -Wall

all: prvocisla prvocisla-inline steg-decode

bit-array.o: bit-array.c bit-array.h
	$(CC) $(CFLAGS) -c bit-array.c -o bit-array.o
bit-array-inline.o: bit-array.c bit-array.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c bit-array.c -o bit-array-inline.o

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o error.o

ppm.o: ppm.c ppm.h error.h
	$(CC) $(CFLAGS) -c ppm.c -o ppm.o

eratosthenes.o: eratosthenes.c eratosthenes.h bit-array.h
	$(CC) $(CFLAGS) -c eratosthenes.c -o eratosthenes.o

eratosthenes-inline.o: eratosthenes.c eratosthenes.h bit-array-inline.o
	$(CC) $(CFLAGS) -c eratosthenes.c -o eratosthenes-inline.o

prvocisla.o: prvocisla.c
	$(CC) $(CFLAGS) -c prvocisla.c -o prvocisla.o

steg-decode.o: steg-decode.c error.h ppm.h bit-array.h eratosthenes.h
	$(CC) $(CFLAGS) -c steg-decode.c -o steg-decode.o

prvocisla: eratosthenes.o prvocisla.o
	$(CC) $(CFLAGS) eratosthenes.o prvocisla.o -o prvocisla -lm

prvocisla-inline: eratosthenes-inline.o prvocisla.o
	$(CC) $(CFLAGS) eratosthenes-inline.o prvocisla.o -o prvocisla-inline -lm

steg-decode: error.o ppm.o eratosthenes.o bit-array.o steg-decode.o
	$(CC) $(CFLAGS) error.o ppm.o eratosthenes.o bit-array.o steg-decode.o -o steg-decode -lm

clean:
	rm *.o prvocisla prvocisla-inline steg-decode
