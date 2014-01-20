#include "Player.h"
#include "AI.h"
#include "Deck.h"
#include "display.h"
#include <deque>
#include <iostream>
#include <string>
#include <typeinfo>
#include <sstream>
#include <algorithm>

using namespace std;

class PokerDriver {
    public:
        PokerDriver();
        ~PokerDriver();

		display DISPLAY;
        int m_InitialPlayers;
        int m_InitialMoney;
        int m_RoundCounter;
        int m_PotMoney;
        deque<Player*> m_Players;
        Deck m_Deck;
        AI m_AiPlayer_0;
        AI m_AiPlayer_1;
        AI m_AiPlayer_2;
        AI m_AiPlayer_3;

        void runAnte();
        void runDeal();
        void runBetting(int bettingCycle);
        void runCardExchange();
        bool roundIsOver();
        bool finishRound();
        void endGame(string endReason);

    protected:
    private:
        void rotatePlayers();
        void removeCurrentPlayer();
        int  getRemainingPotMoney();
        int  unfoldedPlayers();
        void finalizeRound();
        int  ante();
        int  minimumBet(Player *player);
        int  maxSinglePlayerMoney();
        bool allPlayersAllIn();
};
