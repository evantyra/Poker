#include "Player.h"
#include "HumanPlayer.h"
#include "AI.h"
#include "Frame.h"
#include "Deck.h"
#include "display.h"
#include <deque>
#include <iostream>
#include <string>
#include <typeinfo>
#include <sstream>
#include <algorithm>

using namespace std;

class Poker {
    public:
        Poker();
        ~Poker();

        int m_InitialPlayers;
        int m_InitialMoney;
        int m_RoundCounter;
        int m_PotMoney;
        int bettingCycle;
        Frame player0Frame;
        Frame player1Frame;
        Frame player2Frame;
        Frame player3Frame;
        string bannerHeader;
        deque<Player*> m_Players;
        Deck m_Deck;
        HumanPlayer m_HumanPlayer;
        AI m_AiPlayer_1;
        AI m_AiPlayer_2;
        AI m_AiPlayer_3;

        void runAnte();
        void runDeal();
        void runBetting(int bettingCycle);
        void runCardExchange();
        void runShowdown();
        bool roundIsOver();
        bool finishRound();
        void endGame(string endReason);

    protected:
    private:
        void initializeDisplay();
        void setTopBannerText(string text);
        void setBottomBannerText(string text);
        void removePlayer(int position);
        void drawHand(Hand *hand, bool hidden, Frame *frame);
        void updateHand(Hand *hand, Frame *frame);
        void updateGameInfo();
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
