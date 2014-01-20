#include "Player.h"
#include "display.h"

class HumanPlayerStub: public Player {

    public:
	HumanPlayerStub(int displayPos, int initialMoney);
        int bet(int minimumBid, display gameDisplay);
        int discard(display gameDisplay);
};
