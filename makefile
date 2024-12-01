CC = g++
CFLAGS = -g -Wall -std=c++11

a.out: card.h marvel_card.o card.o
	$(CC) $(CFLAGS) marvel_card.o card.o -o a.out

marvel_card.o: marvel_card.cc card.h
	$(CC) -c $(CFLAGS) marvel_card.cc -o marvel_card.o

card.o: card.cc card.h
	$(CC) -c $(CFLAGS) card.cc -o card.o
	
