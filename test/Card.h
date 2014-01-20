#pragma once
#include "Frame.h"
using namespace std;

class Card
{
private:
	int suit;
	int rank;
	bool discard;
	Frame frame;
public:
	Card(int s, int r);
	int getRank();
	int getSuit();
	int getNumber();
	void setDiscarded(bool d);
	bool isDiscarded();
	void setFrame(int x, int y);
	Frame getFrame();
	~Card(void);
};

