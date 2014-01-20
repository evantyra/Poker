#pragma once

#include "Hand.h"
#include "Card.h"
#include <vector>
#include <algorithm>

class Deck
{
public:
    Deck();
    ~Deck();
    void discardCard(Card *c1);
    void shuffle();
    Hand* dealHand();
    Card* drawCard();
    int cardsRemaining();
    int cardsDiscarded();
    int deckIndex;

private:
    vector<Card*> deck;
    vector<Card*> discard; 
};
