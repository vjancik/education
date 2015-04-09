CC = gcc
FILES = proj2.c
EXE = proj2
CFLAGS = -std=c99 -Wall -Wextra  -pedantic 
CLIBS = -lm

build: $(FILES)
	$(CC) $(CFLAGS) $(FILES) $(CLIBS) -o $(EXE) 

clean:
	rm -rf *o $(EXE)
