CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -Werror -pedantic
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
	rm -f h20 *.o xlogin.zip h2o.out

test:
	./check-syntax.sh

pack:
	zip xlogin.zip *.c *.h Makefile

debug: CFLAGS += $(DBGFLAGS)
debug: remake

remake: clean h2o
