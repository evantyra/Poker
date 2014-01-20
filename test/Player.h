#pragma once

#include "Hand.h"
#include "display.h"

class Player {

    protected:
        int displayPosition;
        int money;
        int moneyInPot;
        bool hasFolded;
        Hand *hand;
        Frame *frame;

    public:
        static const int CALL = 0;
        static const int CHECK = 0;
        static const int FOLD = -1;
        static const int ALL_IN = -2;

    	Player(int displayPos, int initialMoney);
	    virtual ~Player();

        virtual int bet(int minimumBid, display gameDisplay) = 0;
        virtual int discard(display gameDisplay) = 0;

        Hand* getHand();
        void setHand(Hand *newHand);

        int getMoney();
        int getMoneyInPot();
	    int giveMoney(int amount);
	    void setMoney(int amount);
        void setMoneyInPot(int amount);

        bool folded();
        void setFolded(bool fold);

        void setFrame(Frame* newFrame);
        Frame* getFrame();

	    void setDisplayPosition(int position);
	    int getDisplayPosition();

        int ante(int anteAmount, display gameDisplay);
};
