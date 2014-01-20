#include "Deck.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

/*
Constructs an unshuffled deck of card pointers. Call shuffle before use
*/
Deck::Deck()
{
    std::srand(unsigned(std::time(0)));     //Seed rand()
    deckIndex = 51;
    for (int rank = 2; rank < 15; rank++) {     //14 card rankings
        for (int suit = 0; suit < 4; suit++){   //4 suits
        	Card* c1 = new Card(suit,rank);
            deck.push_back(c1);
        }
    }
}

/*
Destroys the calling deck object
*/
Deck::~Deck()
{
    for (int i = 0; i < 52; i++)
    {
    	delete deck.at(i);
    }
    discard.clear();
    deck.clear();
    deckIndex = 51;
}

/*
Sends a pointer to a Card to the discard pile
*/
void Deck::discardCard(Card* c1)
{
    if (discard.size() < 53)
    {
    	c1->setDiscarded(true);
        discard.push_back(c1);
    }
}

/*
Shuffles the current full deck of cards.
*/
void Deck::shuffle()
{
	discard.clear();
	for (int i = 0; i < 52; i++)
	{
		deck.at(i)->setDiscarded(false);
	}
    std::random_shuffle(deck.begin(),deck.end());
    deckIndex = 51;
}

/*
Returns a five card hand from the deck. Used only at the start of new rounds.
*/
Hand* Deck::dealHand()
{
	/*Card* temp0 = deck.at(deckIndex);
	Card* temp1 = deck.at(deckIndex-1);
	Card* temp2 = deck.at(deckIndex-2);
	Card* temp3 = deck.at(deckIndex-3);
	Card* temp4 = deck.at(deckIndex-4);
	return new Hand(temp0,temp1,temp2,temp3,temp4);*/
    Hand *h1 = new Hand(deck[deckIndex], deck[deckIndex-1], deck[deckIndex-2], deck[deckIndex-3], deck[deckIndex-4]);
    deckIndex-=5;
    return h1;
}

/*
Draws a single card from a deck that has at least one card remaining. Used for replacement cards.
*/
Card* Deck::drawCard()
{
    deckIndex--;
    return deck[deckIndex+1];
    //return new Card(rand() % 4, 5); //always return a 5 of a random suit. Test.
}

/*
Returns the number of cards left in the deck. A return value of -1 means the deck is empty.
*/
int Deck::cardsRemaining()
{
    return deckIndex+1;
    //return rand() % 53;       //used for testing deck under different conditions
}

/*
Returns the number of cards that have been discarded.
*/
int Deck::cardsDiscarded()
{
    return discard.size();
    //return 0;     //discard pile not ready yet
}
