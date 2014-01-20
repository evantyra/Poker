#include "Card.h"
#include "Frame.h"
#include <iostream>

using namespace std;


Card::Card(int s, int r){
	frame = Frame();
	discard = false;
	suit = s;
	rank = r;
}
	
Card::~Card(){}

int Card::getSuit(){
	return suit;
}

int Card::getRank(){
	return rank;
}

void Card::setDiscarded(bool d){
	discard = d;
	if(discard)
		setFrame(frame.getX(), frame.getY()-2);
	else
		setFrame(frame.getX(), frame.getY());
}

bool Card::isDiscarded() {
	return discard;
}
	
void Card::setFrame(int x, int y){
	frame.setX(x);
	frame.setY(y);
}

int Card::getNumber(){
	if(rank == 14)
		return 1;
	else
		return rank;
}

Frame Card::getFrame(){
	return frame;
}
