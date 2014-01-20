#pragma once
#include "Hand.h"

class HandDriver
{
public:
	HandDriver(void);
	int main();
	void testHand(Hand hand, int *expectedArray, bool higherThanThreeOfAKind, int cardExchanged,
					Card* exchangedCard, int elementGot, Card* gotCard);
	~HandDriver(void);
};