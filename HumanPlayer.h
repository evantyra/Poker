#include "Player.h"
#include "display.h"

class HumanPlayer: public Player {

    public:
	HumanPlayer(int displayPos, int initialMoney);
        int ante(int minimumAnte, display gameDisplay);
        int bet(int minimumBet, display gameDisplay);
        int discard(display gameDisplay);
};
