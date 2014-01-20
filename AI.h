#include "Player.h"
#include "display.h"


class AI: public Player {
	
public:
	AI(int displayPos, int startingMoney);
	int bet(int minimumBid, display gameDisplay);
	int discard(display gameDisplay);
	int ante(int anteamount, display gameDisplay);
};
