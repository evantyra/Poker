#pragma once
#include "Card.h"
#include <vector>

using namespace std;

class Hand{
private:
	vector<Card*> hand;
	int ranks[13];
	
public: 
	Hand(Card *c1, Card *c2, Card *c3, Card *c4, Card *c5);
	Card* exchange(Card* c, int placeOfCard);
	bool isHigherScore(int secondScore[15]);
	bool compareTo(int secondScore[15]);
	void highCard(int *score);
	bool isDouble(int *score);
	bool isTwoPair(int *score);
	bool isThreeofaKind(int *score);
	bool isStraight(int *score);
	bool isFlush(int *score);
	bool isFullHouse(int *score);
	bool isFourofaKind(int *score);
	bool isStraightFlush(int *score);
	int* getScore();
	Card* getCard(int element);
};

