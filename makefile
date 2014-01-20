CC = g++
CFLAGS = -Wall -c
LFLAGS = -lncursesw

all: poker

poker: display.o Frame.o Card.o Hand.o Deck.o Player.o HumanPlayer.o AI.o Poker.o 
	 $(CC) Poker.cpp display.o Frame.o Card.o Hand.o Deck.o Player.o HumanPlayer.o AI.o -o poker $(LFLAGS)

Frame.o: Frame.cpp Frame.h
	$(CC) $(CFLAGS) Frame.cpp

Card.o: Card.cpp Card.h
	$(CC) $(CFLAGS) Card.cpp

Hand.o: Hand.cpp Hand.h
	$(CC) $(CFLAGS) Hand.cpp

Deck.o: Deck.cpp Deck.h
	$(CC) $(CFLAGS) Deck.cpp

Player.o: Player.cpp Player.h
	$(CC) $(CFLAGS) Player.cpp

HumanPlayer.o: HumanPlayer.cpp HumanPlayer.h
	$(CC) $(CFLAGS) HumanPlayer.cpp
	
AI.o: AI.cpp AI.h
	$(CC) $(CFLAGS) AI.cpp

clean:
	rm -f *.o *~ poker
