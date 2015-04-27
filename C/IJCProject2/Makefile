CC = gcc
CFLAGS = -std=c99 -Wall -Wextra
DBGFLAGS = -g

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c,%.o,$(SRC))

tail : $(OBJ)
	$(CC) $^ -o $@ $(CFLAGS)

%.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: clean pack debug

clean:
	rm -f tail *.o xjanci09.zip

pack:
	zip xjanci09.zip *.c *.h Makefile

debug: CFLAGS += $(DBGFLAGS)
debug: clean tail
