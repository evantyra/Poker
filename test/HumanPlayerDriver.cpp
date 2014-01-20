/**
 * Author: John Shield
 * Modified by: Michael Bjorge
 */
#include "display.h"
#include "Card.h"
#include "Hand.h"
#include "Deck.h"
#include "HumanPlayer.h"
#include "HumanPlayerStub.h"
#include <signal.h>
#include <ncurses.h>
#include <cstdlib>
#include <sstream>
#include <assert.h>

using namespace std;

int main(int argc, char* argv[])
{
    // using a stringstream rather than a string to make making the banner easier
    stringstream messageString;

    display gameDisplay;

    cout << "Making a deck" << endl;
    Deck deck;
    Hand *hand;
    cout << "Dealing a hand" << endl;
    hand = deck.dealHand();

    cout << "Making a player" << endl;
    HumanPlayer human(0, 500);
    human.setHand(hand);

    assert(human.getMoney() == 500);
    assert(human.getDisplayPosition() == 0);
    cout << "Success: Constructor" << endl;
    cout << "Success: getMoney" << endl;
    cout << "Success: getDisplayPosition" << endl;

    assert(human.giveMoney(1056) == 1556);
    cout << "Success: giveMoney" << endl;   

    human.setMoney(2500);
    assert(human.getMoney() == 2500);
    cout << "Success: setMoney" << endl;

    assert(human.folded() == false);
    cout << "Success: folded" << endl;

    int ante = human.ante(10, gameDisplay);
    if (ante == Player::FOLD) {
        cout << "Success: Ante fold" << endl;
    } else {
        ante = 10;
    }

    int bet = human.bet(30, gameDisplay);
    int numDiscards = human.discard(gameDisplay);

    if (bet == Player::FOLD) {
        assert(human.getMoneyInPot() == 10);
        assert(human.getMoneyInPot() + human.getMoney() == 2500);
        cout << "Success: fold" << endl;
    } else if (ante != Player::FOLD) {
        assert(human.getMoneyInPot() == bet + ante);
        assert(human.getMoneyInPot() + human.getMoney() == 2500);
        cout << "Success: bet" << endl;
    }

    int i, discardCount = 0;
    for (i = 0; i < 5; i++) {
        if (hand->getCard(i)->isDiscarded()) {
            discardCount++;
        }
    }
    assert(discardCount == numDiscards);
    cout << "Success: discard" << endl;

    cout << "Success: Player and HumanPlayer methods" << endl; 
    return 0;
}
