CC = gcc
CFLAGS = -Wall -std=c99

all: wordle

wordle.o: wordle.c lexicon.h io.h
	gcc -g -Wall -std=c99   -c -o wordle.o wordle.c
io.o: io.c io.h
	gcc -g -Wall -std=c99   -c -o io.o io.c
lexicon.o: lexicon.c lexicon.h
	gcc -g -Wall -std=c99   -c -o lexicon.o lexicon.c
history.o: history.c history.h
	gcc -g -Wall -std=c99   -c -o history.o history.c

wordle: wordle.o io.o lexicon.o history.o
	gcc wordle.o lexicon.o history.o io.o -o wordle

clean:
	rm -f wordle.o lexicon.o io.o history.o
	rm -f wordle
	rm -f scores.txt
	rm -f output.txt
	rm -f stderr.txt