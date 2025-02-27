CC = g++
CFLAGS = -g -Wall -std=c++11

play: card.h marvel_card.o card.o
	$(CC) $(CFLAGS) marvel_card.o card.o -o play

marvel_card.o: marvel_card.cc card.h
	$(CC) -c $(CFLAGS) marvel_card.cc -o marvel_card.o

card.o: card.cc card.h
	$(CC) -c $(CFLAGS) card.cc -o card.o

clean:
	rm card.o marvel_card.o	
