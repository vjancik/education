CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra
DBGFLAGS = -g
LDLIBS = -pthread

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c,%.o,$(SRC))

h2o : $(OBJ)
	$(CC) $^ -o $@ $(CFLAGS) $(LDLIBS)

%.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: clean test pack debug remake

clean:
	rm -f h2o *.o h2o.out

test:
	./check-syntax.sh

pack:
	zip *.c *.h Makefile

debug: CFLAGS += $(DBGFLAGS)
debug: remake

remake: clean h2o
