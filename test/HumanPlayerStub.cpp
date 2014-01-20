#include "HumanPlayerStub.h"
#include "display.h"
#include <string>

HumanPlayerStub::HumanPlayerStub(int displayPos, int initialMoney) : Player(displayPos, initialMoney) {}

int HumanPlayerStub::bet(int minimumBid, display gameDisplay) {
    if (money < minimumBid) {
        return Player::FOLD;
    }

    int bid = 0;

    //Take the minBid mod 3 to give three different possible tests
    switch (minimumBid % 3) {
        case 0:
            bid = minimumBid;
            break;
        case 1:
            bid = money;
            break;
        case 2:
            bid = (minimumBid + money) / 2;
            break;
        default:
            bid = Player::FOLD;
    }

    moneyInPot += bid;
    money -= bid;
    return bid;
}

int HumanPlayerStub::discard(display gameDisplay) {
    int i;
    for (i = 0; i < 5; i++) {
        hand->getCard(i)->setDiscarded(false);
    }

    hand->getCard(0)->setDiscarded(true);
    hand->getCard(4)->setDiscarded(true);
    hand->getCard(2)->setDiscarded(true);

    return 3;
}
            
