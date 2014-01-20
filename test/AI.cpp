#include "AI.h"
#include <cstdlib>
#include <ctime>

using namespace std;

AI::AI(int displayPos, int initialMoney) : Player(displayPos, initialMoney) {}

int AI::bet(int minimumbid, display gameDisplay)
{
    std::srand(unsigned(std::time(0)));
    int random = rand() % 10;
    if (random == 0) {
        hasFolded = true;
        return Player::FOLD;
    } else if (random < 7) {
        int bid = minimumbid;
        money -= bid;
        moneyInPot += bid;
        return bid;
    }
    
    if (money >= minimumbid)
    {
        int bid = rand() % (money - minimumbid) + minimumbid;    
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
