#include "AI.h"
#include <cstdlib>
#include <ctime>

using namespace std;

AI::AI(int displayPos, int initialMoney) : Player(displayPos, initialMoney) {
    std::srand(unsigned(std::time(0)));
}


int AI::bet(int minimumbid, display gameDisplay)
{
    int random = rand() % 10;
    if (random == 0) {
        hasFolded = true;
        return Player::FOLD;
    } else if (random < 7) {
        int bid = min(minimumbid, money);
        money -= bid;
        moneyInPot += bid;
        return bid;
    }
    
    if (money >= minimumbid)
    {
        double multiplier = 1.0 / (double)(rand() % 100 + 1);
        int maxBid = (int) (multiplier * money);
        maxBid = max(minimumbid + 1, maxBid);
        int bid = rand() % (maxBid - minimumbid) + minimumbid;    
        money -= bid;
        moneyInPot += bid;
        return bid;      //AI bets minimum amount each time it is asked to bet
    }
    else
    {
        int bid = money;
        moneyInPot += bid;
        money -= bid;
        return bid;           //Have to go all in once money < minimum bid
    }
    //return minimumbid; //basic functionality. Use this result for testing
}

int AI::discard(display gameDisplay)
{
	for (int i = 0; i < 5; i++) {		//Reset discard flags just in case
		hand->getCard(i)->setDiscarded(false);
	}

    int discardCount = 2;
    hand->getCard(0)->setDiscarded(true);     //Discard 0th card
    hand->getCard(3)->setDiscarded(true);	//Discard 3rd card
    return discardCount;
}

int AI::ante(int anteamount, display gameDisplay)
{
    if (money >= anteamount) {
        moneyInPot += anteamount;
        money -= anteamount;
    	return anteamount;
	} else {
	    return Player::FOLD;
    }
}
