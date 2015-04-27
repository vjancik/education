CC = gcc
CFLAGS = -std=c99 -Werror -Wall -pedantic
DBGFLAGS =  -g3

INCLUDE = -I../curl/include
LDFLAGS = -L../curl/lib/
LDLIBS = -lcurl

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c,%.o,$(SRC))

calc-parity: $(OBJ)
	$(CC) $^ -o $@ $(INCLUDE) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

%.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

.PHONY: clean test pack debug

clean:
	rm -rf *.o calc-parity downloads ref *~

test:
	./test.sh

pack:
	zip -r calc-parity.zip *.c *.h Makefile test test.sh  mockup.pdf protokol.pdf .git .gitignore

debug: CFLAGS += $(DBGFLAGS)
debug: clean calc-parity
