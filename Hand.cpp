#include <iostream>
#include <vector>
#include "Hand.h"
#include "Card.h"

using namespace std;

Hand::Hand(Card *c1, Card *c2, Card *c3, Card *c4, Card *c5){
	for(int i = 0; i < 13; i++)		// Initializes ranks array
		ranks[i] = 0;

	hand.resize(5);
	hand[0] = c1;
	hand[1] = c2;
	hand[2] = c3;
	hand[3] = c4;
	hand[4] = c5;

	for(int i = 0; i < 5; i++){
		ranks[hand[i]->getRank() - 2]++;
		// Keeps track of how many of each rank you have in your hand,
		// the "- 2" is there to allow for good memory usage and no empty array spots
	}
}

bool Hand::isHigherScore(int secondScore[15]){
	int *score = getScore();

	// int temp[] = {0,0,0,0,0,0,0,0,0,0,6,5,4,3,2};
	// int *score = temp;

	for(int i = 0; i < 15; i++){
		if(score[i] > secondScore[i])
			return true;
		else if(score[i] < secondScore[i])
			return false;
	}
	return true;
}

Card* Hand::exchange(Card* c, int placeOfCard){
	Card* temp = hand[placeOfCard];
	hand[placeOfCard] = c;

	for(int i = 0; i < 13; i++)				// The following is a repeat of the constructor
		ranks[i] = 0;						// This resets the ranks array

	for(int i = 0; i < 5; i++){
		ranks[hand[i]->getRank() - 2]++;
	}

	return temp;
}

	// From 0 -> 14 this is what each element of the array stands for
	// Straight Flush, 4 of a Kind, Full House 3-pair, Full House 2-pair, Flush High-Card, Straight High Card, 3 of a Kind, 2 Pair High-Pair, 2 Pair Low-Pair, Double, Last 5 High Cards in descending
	// 0 ------------> 1 ----------> 2 ---------------> 3 ----------------> 4 ------------> 5 ---------------> 6 ---------> 7 ---------------> 8 -------------> 9 ----> 10, 11, 12, 13, 14
int* Hand::getScore(){
	int *score = new int[15];

	for(int i = 0; i < 15; i++)	// Initializes all spots in the array as zero
		score[i] = 0;

	// Goes through and checks for each scoring, gets rid of paradoxes of double and two-pair with else if
	if(isStraightFlush(score))
		return score;
	else if(isFourofaKind(score))
		return score;
	else if(isFullHouse(score))
		return score;
	else if(isFlush(score))
		return score;
	else if(isStraight(score))
		return score;
	else if(isThreeofaKind(score))
		return score;
	else if(isTwoPair(score))
		return score;
	else if(isDouble(score))
		return score;
	else{ // Case of High Card
		highCard(score);
		return score;
	}

	// int temp[] = {0,0,0,0,0,0,0,0,0,0,6,5,4,3,2};
	// return temp;
}

void Hand::highCard(int *score){
	// High Card Calculation
	int currentHC = 0; // Allows me to keep track how many high cards I've recorded
	for(int i = 12; i >= 0; i--){
		if(ranks[i] == 1){
			score[currentHC + 10] = i + 2;
			currentHC++;
		}
	}

	// int temp[] = {0,0,0,0,0,0,0,0,0,0,6,5,4,3,2};
	// score = temp;
}

bool Hand::isDouble(int *score){
	for(int i = 0; i < 13; i++){
		if(ranks[i] == 2){	//If there are two of a rank in the hand then there is a double
			score[9] = i + 2;
			highCard(score);	// Calculates the high cards in the hand
			return true;
		}
	}
	return false;

	/* int temp[] = {0,0,0,0,0,0,0,0,0,2,6,5,4,0,0};
	** score = temp;
	** return true;	*/
}

bool Hand::isTwoPair(int *score){
	for(int i = 0; i < 13; i++){
		if(ranks[i] == 2){	// If there is atleast a double in the for hand it will check for another double
			for(int k = i + 1; k < 13; k++){
				if(ranks[k] == 2){
					score[7] = k + 2;	// High pair of 2-pair
					score[8] = i + 2;	// Low pair of 2-pair
					highCard(score);
					return true;
				}
			}
		}
	}
	return false;

	/* int temp[] = {0,0,0,0,0,0,0,3,2,0,6,0,0,0,0};
	** score = temp;
	** return true;	*/
}

bool Hand::isThreeofaKind(int *score){
	for(int i = 0; i < 13; i++){
		if(ranks[i] == 3){
			score[6] = i + 2;
			highCard(score);
			return true;
		}
	}
	return false;

	/* int temp[] = {0,0,0,0,0,0,3,0,0,0,6,0,0,0,0};
	** score = temp;
	** return true;	*/
}

bool Hand::isStraight(int *score){
	int cardsInARow = 0;	// Keeps track of how many cards are in a row
	int highestCard = 0;	// Keeps track of the highest card in a straight if there is a straight
	for(int i = 12; i >= 0; i--){
		if(ranks[i] == 1){
			if(cardsInARow == 0)
				highestCard = i + 2;
			cardsInARow++;
		}
		else
			cardsInARow = 0;

		if(cardsInARow == 5){
			score[5] = highestCard;
			return true;
		}
	}

	if(cardsInARow == 4 && ranks[12] == 1){ // Edge Case where ace counts as low instead of high
		score[5] = 5;
		return true;
	}
	return false;

	/* int temp[] = {0,0,0,0,0,6,0,0,0,0,6,5,4,3,2};
	** score = temp;
	** return true;	*/
}

bool Hand::isFlush(int *score){
	int suits[] = {0,0,0,0};
	for(int i = 0; i < 5; i++)	// Counts how many of each suit are in a hand
		suits[hand.at(i)->getSuit()]++;

	for(int i = 0; i < 4; i++){	// Sees if there are 5 of one suit in a hand.
		if(suits[i] == 5){
			for(int i = 12; i >= 0; i--){	// Used for checking the highest card in the hand
				if(ranks[i] == 1){
					score[4] = i+2;		// Records the highest card in the hand
					break;			// Breaks loop
				}
			}
			highCard(score);
			return true;
		}
	}

	return false;

	/* int temp[] = {0,0,0,0,7,0,0,0,0,0,7,5,4,3,2};
	** score = temp;
	** return true;	*/
}

bool Hand::isFullHouse(int *score){
	for(int i = 0; i < 13; i++){
		if(ranks[i] == 2){	// If there is atleast a double in the for hand it will then check for a triple
			for(int k = 0; k < 13; k++){
				if(ranks[k] == 3){
					score[3] = i + 2;	// Double of the Full House
					score[2] = k + 2;	// Triple of the Full House
					highCard(score);
					return true;
				}
			}
		}
	}
	return false;

	/* int temp[] = {0,0,5,4,0,0,0,0,0,0,0,0,0,0,0};
	** score = temp;
	** return true;	*/
}

bool Hand::isFourofaKind(int *score){
	for(int i = 0; i < 13; i++){
		if(ranks[i] == 4){
			score[1] = i+2;
			highCard(score);
			return true;
		}
	}

	return false;

	/* int temp[] = {0,2,0,0,0,0,0,0,0,0,7,0,0,0,0};
	** score = temp;
	** return true;	*/
}

bool Hand::isStraightFlush(int *score){
	if(isFlush(score) && isStraight(score)){
		score[0] = score[4];
		score[4] = 0;
		score[5] = 0;
		return true;
	}

	return false;

	/* int temp[] = {7,0,0,0,0,0,0,0,0,0,7,5,4,3,2};
	** score = temp;
	** return true;	*/
}

Card* Hand::getCard(int element){
	return hand[element];
}
