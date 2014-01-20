#include "HumanPlayer.h"
#include "display.h"
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

HumanPlayer::HumanPlayer(int displayPos, int initialMoney) : Player(displayPos, initialMoney) {}

/**
* Ask the player if they want to ante. If they fold,
* remove them from the game. If they call, proceed normally.
*  - Alex
*/
int HumanPlayer::ante(int minimumAnte, display gameDisplay) {
    int input;

    stringstream bannerText;
    bannerText << "Current Ante: " << minimumAnte << "; a:ante up; l:leave game";
    gameDisplay.bannerBottom(bannerText.str());

    //check if player has enough money
    if (money < minimumAnte) {
        bannerText.str("");
        bannerText << "Ante is " << minimumAnte << "; You do not have enough money to ante. Ending game. <Press any key to continue>";
        gameDisplay.bannerBottom(bannerText.str());
        while (1) {
            input = gameDisplay.captureInput();
            if (input != 0) {
                return Player::FOLD;
            }
        }
    }

    while (1) {
		input = gameDisplay.captureInput();

		switch (input) {
            case 'a': case 'A':
                moneyInPot += minimumAnte;
                money -= minimumAnte;
                return Player::CALL;

            case 'l': case 'L':
                return Player::FOLD;
		}
    }
}

/**
 * Ask the player how much they want to bid.
 * Once a legal bid is made, subtract the bid from the player's money.
 * Note: If a player bids more than they have, they go all in.
 * Add the player's bid to the player's moneyInPot.
 * If the player folds, set the fold flag for that player.
 * returns the amount bid, unless the player folds, in which case Player::FOLD is returned
 */

int HumanPlayer::bet(int minimumBet, display gameDisplay) {
	int currentBid = 0;
	int input;

    if (hasFolded) {
        return Player::FOLD;
    }

	stringstream bannerText;
	if (money < minimumBet) {
        bannerText << "Call: " << minimumBet << "; Not enough money; f:fold; a:all in;" << currentBid << "  ";
	} else {
        bannerText << "Minimum: " << minimumBet << "; f:fold; c:call/check; a:all in; current bid: " << currentBid << "  ";
	}

	gameDisplay.bannerBottom(bannerText.str());

	while (1) {
		input = gameDisplay.captureInput();

        //If the bid ever becomes negative, something went wrong, so reset it.
        if (currentBid < 0) {
            currentBid = 0;
        } else if (currentBid > money) {
            currentBid = money;
        }

        if (money < minimumBet) {
            switch (input) {
            //Fold
            case 'f': case 'F':
                hasFolded = true;
                return Player::FOLD;

            //All In
            case 'a': case 'A':
                currentBid = money;
                moneyInPot += currentBid;
                money -= currentBid;
                return currentBid;
            }
        } else {
            switch (input) {
            //The player typed a number, so update the bid accordingly
            case '0': case '1': case '2':
            case '3': case '4': case '5':
            case '6': case '7': case '8':
            case '9':
                currentBid = (currentBid) * 10 + (input - '0');
                currentBid = min(currentBid, money);
                bannerText.str("");
                bannerText << "Minimum: " << minimumBet << "; f:fold; c:call/check; a:all in; current bid: " << currentBid << "  ";
                gameDisplay.bannerBottom(bannerText.str());
                break;

            //Fold
            case 'f': case 'F':
                hasFolded = true;
                return Player::FOLD;

            //Call/Check
            case 'c': case 'C':
                currentBid = minimumBet;
                moneyInPot += currentBid;
                money -= currentBid;
                return currentBid;

            //All In
            case 'a': case 'A':
                currentBid = money;
                moneyInPot += currentBid;
                money -= currentBid;
                return currentBid;

            //Backspace and delete characters
            case 8: case 127: case 330: case 263:
                currentBid = currentBid/10;
                bannerText.str("");
                bannerText << "Minimum: " << minimumBet << "; f:fold; c:call/check; a:all in; current bid: " << currentBid << "  ";
                gameDisplay.bannerBottom(bannerText.str());
                break;

            //Player pressed ENTER, b, or B (for Bid), r or R (for Raise)
            case '\r': case 10: case 'b': case 'B': case 'r': case 'R':
                if (currentBid < minimumBet) {
                    currentBid = 0;
                    bannerText.str("");
                    bannerText << "ERROR: Bid too low; Minimum: " << minimumBet << "; f:fold; c:call/check; a:all in; current bid: " << currentBid << "  ";
                    gameDisplay.bannerBottom(bannerText.str());
                } else if (currentBid >= money) { //If a player bids more than they have, they go all in
                   currentBid = money;
                    moneyInPot += currentBid;
                    money -= currentBid;
                    return currentBid;
                } else if (currentBid == 0) {
                    return Player::CHECK;
                } else {
                    moneyInPot += currentBid;
                    money -= currentBid;
                    return currentBid;
                }
                break;
            }
        }
	}
}

/**
 * Ask the player which cards they want to discard
 * Set the discard flag for each card the player wants to discard
 * Return the number of cards the player wants to discard
 */
int HumanPlayer::discard(display gameDisplay) {
    int input;
    stringstream bannerText;
    bannerText << "Cards to discard: <Press ENTER or (d) when done>";
    gameDisplay.bannerBottom(bannerText.str());

    //Reset all the discard flags
    int i;
    for (i = 0; i < 5; i++) {
        hand->getCard(i)->setDiscarded(false);
    }

	while (1) {
        input = gameDisplay.captureInput();

        int cardIndex = 0;

        switch(input) {
            //Player indicates a card 1-5, so toggle that card's discard flag
            case '1': case '2':
            case '3': case '4':
            case '5':
                cardIndex = input - '1';
                hand->getCard(cardIndex)->setDiscarded(!hand->getCard(cardIndex)->isDiscarded());
                break;

            //Backspace and delete buttons, removes the right-most discard
            case 8: case 127: case 330: case 263:
                for (i = 4; i >= 0; i--) {
                    if (hand->getCard(i)->isDiscarded()) {
                        hand->getCard(i)->setDiscarded(false);
                        break;
                    }
                }
                break;

            //Player pressed ENTER, d, D (for discard), so discard the selected cards.
            case '\r': case 10: case 'd': case 'D':
                int discardCount = 0;
                for (i = 0; i < 5; i++) {
                    if (hand->getCard(i)->isDiscarded()) {
                        discardCount++;
                    }
                }
                return discardCount;
        }

        //Update the banner text to show which cards are currently selected for discard
        if (input != 0) {
            bannerText.str("Cards to discard: ");
            for (i = 0; i < 5; i++) {
                if (hand->getCard(i)->isDiscarded()) {
                    bannerText << (i+1) << " ";
                }
            }
            bannerText << "<Press ENTER or (d) when done>";
            gameDisplay.bannerBottom(bannerText.str());
        }
	}
}
