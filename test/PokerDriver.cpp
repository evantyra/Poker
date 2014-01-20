#include "PokerDriver.h"
#include "display.h"


PokerDriver::PokerDriver() :
    m_InitialPlayers(4),
    m_InitialMoney(10000),
    m_RoundCounter(1),
    m_PotMoney(0),
    m_AiPlayer_0(0, m_InitialMoney),
    m_AiPlayer_1(1, m_InitialMoney),
    m_AiPlayer_2(2, m_InitialMoney),
    m_AiPlayer_3(3, m_InitialMoney),
    m_Players()

{
    m_Players.push_back(&m_AiPlayer_0);
    m_Players.push_back(&m_AiPlayer_1);
    m_Players.push_back(&m_AiPlayer_2);
    m_Players.push_back(&m_AiPlayer_3);
}

PokerDriver::~PokerDriver() {}

#pragma mark - deque manipulate methods

void PokerDriver::rotatePlayers() {
    Player *tempPlayer = m_Players.front();
    m_Players.pop_front();
    m_Players.push_back(tempPlayer);

    if (m_Players.back() != tempPlayer)
        cout << "FAILURE_1" << endl;
}

void PokerDriver::removeCurrentPlayer() {
    m_Players.pop_front();
}

#pragma mark - Game Play

void PokerDriver::runAnte() {
    int a = ante();

    for (int i = 0; i < m_Players.size(); i++) {
        Player *player = m_Players.front();

        if(player->ante(a, DISPLAY) == Player::FOLD) {
            continue;
        }

        m_PotMoney += player->getMoneyInPot();

        rotatePlayers();
        cout << "Ante_" << i << "_SUCCESS" << endl;
    }
}

void PokerDriver::runDeal() {
    int i;

    for (i = 0; i < rand() %1000; i++)
        m_Deck.shuffle();

    for (i = 0; i < m_Players.size(); i++) {
        Card *c1 = m_Deck.drawCard();
        Card *c2 = m_Deck.drawCard();
        Card *c3 = m_Deck.drawCard();
        Card *c4 = m_Deck.drawCard();
        Card *c5 = m_Deck.drawCard();
        m_Players[i]->setHand( new Hand(c1, c2, c3, c4, c5) );
        cout << "Hand_Deal_SUCCESS" << endl;

        if (m_Players[i]->getHand() == NULL)
            cout << "FAILURE_2" << endl;
    }
}

void PokerDriver::runBetting(int bettingCycle) {
    int bet, callCounter = 0, minBet;

    while (unfoldedPlayers() > 1) {
        Player *player = m_Players.front();
        minBet = minimumBet(player);

        if (player->folded()) {
            callCounter++;
        } else {
            bet = player->bet(minBet, DISPLAY);
            cout << "Bet_SUCCESS" << endl;
            callCounter++;

            if (bet != Player::FOLD) {
                m_PotMoney += bet;

                if (bet > minBet) {
                    callCounter = 1;
                }
            }
        }

        if (callCounter >= unfoldedPlayers() || allPlayersAllIn())
            break;

        rotatePlayers();
    }
}

int PokerDriver::unfoldedPlayers() {
    int unfolded = 0;

    for (int i = 0; i < m_Players.size(); i++) {
        unfolded += (int) !m_Players[i]->folded();
    }

    if (unfolded < 1)
        cout << "FAILURE_3" << endl;

    return unfolded;
}

void PokerDriver::runCardExchange() {
    for (int i = 0; i < m_Players.size(); i++) {
        Player *player = m_Players.front();

        if (!player->folded()) {
            player->discard(DISPLAY);

            cout << "Discard_SUCCESS" << endl;

            for (int j = 0; j < 5; j++) {
                if (player->getHand()->getCard(j)->isDiscarded()) {
                    m_Deck.discardCard(player->getHand()->exchange(m_Deck.drawCard(), j));
                    cout << "Discard_SUCCESS" << endl;
                }
            }
        }

        rotatePlayers();
    }
}

bool PokerDriver::roundIsOver() {
    if (m_Players.size() == 1) return true;

    Player *winner;

    if (unfoldedPlayers() == 1) {
        for (int i = 0; i < m_Players.size(); i++) {
            if (!m_Players[i]->folded()) {
                winner = m_Players[i];
                break;
            }
        }
        winner->giveMoney(m_PotMoney);

        finalizeRound();
        return true;
    }

    return false;
}

int PokerDriver::getRemainingPotMoney(){
    int sum = 0;
    for(int i = 0; i < m_Players.size(); i++){
        sum += m_Players[i]->getMoneyInPot();
    }
    return sum;
}

bool PokerDriver::finishRound() {
    Player* winner = NULL;
    int *score;

    for(int i = 0; i < m_Players.size(); i++){
        if (!m_Players[i]->folded() && m_Players[i]->getMoneyInPot() > 0) {
            if (winner == NULL) {
                winner = m_Players[i];
                score = winner->getHand()->getScore();
            } else if (m_Players[i]->getHand()->isHigherScore(score)) {
                winner = m_Players[i];
                score = winner->getHand()->getScore();
            }
        }
    }

    while(getRemainingPotMoney() > 0){
        winner = NULL;
        int *highscore;

        //Determine the winningest player with non-zero pot money left
        for(int i = 0; i < m_Players.size(); i++){
            if (!m_Players[i]->folded() && m_Players[i]->getMoneyInPot() > 0) {
                if (winner == NULL) {
                    winner = m_Players[i];
                    highscore = winner->getHand()->getScore();
                } else if (m_Players[i]->getHand()->isHigherScore(highscore)) {
                    winner = m_Players[i];
                    highscore = winner->getHand()->getScore();
                }
            }
        }

        //Add money to the bank
        for (int i = 0; i < m_Players.size(); i++) {
            winner->giveMoney(min(winner->getMoneyInPot(), m_Players[i]->getMoneyInPot()));
        }

        vector<int> tmpPotMoney(m_Players.size());
        int winnerPotMoney = winner->getMoneyInPot();

        for (int i = 0; i < m_Players.size(); i++) {
            tmpPotMoney[i] = m_Players[i]->getMoneyInPot();
        }

        //Updates remaining money in the pot
        for (int i = 0; i < m_Players.size(); i++) {
            m_Players[i]->setMoneyInPot(max(tmpPotMoney[i] - winnerPotMoney, 0));
        }
    }



    finalizeRound();
    return true;
}

void PokerDriver::finalizeRound() {
    for (int i = 0; i < m_Players.size(); i++) {
        m_Players[i]->setMoneyInPot(0);

        if (m_Players[i]->getMoneyInPot() != 0)
            cout << "Get_Money_FAILURE" << endl;
    }

    m_PotMoney = 0;
    Hand *hand;
    for (int i = 0; i < m_Players.size(); i++) {
        m_Players[i]->setFolded(false);
        hand = m_Players[i]->getHand();

        if (hand->getCard(2) != NULL)
            cout << "Get_Card_SUCCESS" << endl;
        else
            cout << "FAILURE_5" << endl;

        for (int j = 0; j < 5; j++) {
            m_Deck.discardCard(hand->getCard(j));
            cout << "Discard_SUCCESS" << endl;
        }
    }
}

void PokerDriver::endGame(string endReason) {
    cout << endReason << endl;
    exit(0);
}

#pragma mark - Misc. Controls

int PokerDriver::ante() {
    int num_players = m_Players.size();
    switch (num_players) {
        case 4:
            return (int) (0.015 * (double)m_InitialMoney * (double)m_InitialPlayers);
            break;
        case 3:
            return (int) (0.025 * (double)m_InitialMoney * (double)m_InitialPlayers);
            break;
        case 2:
            return (int) (0.15 * (double)m_InitialMoney * (double)m_InitialPlayers);
            break;
        default:
            return 0;
            break;
    }
}

int PokerDriver::minimumBet(Player *player) {
    return ( maxSinglePlayerMoney() - player->getMoneyInPot() );
}

int PokerDriver::maxSinglePlayerMoney() {
    return max( m_AiPlayer_0.getMoneyInPot(), max( m_AiPlayer_1.getMoneyInPot(), max( m_AiPlayer_2.getMoneyInPot(), m_AiPlayer_3.getMoneyInPot() ) ) );
}

bool PokerDriver::allPlayersAllIn() {
    bool allIn = true;
    for (int i = 0; i <  m_Players.size(); i++) {
        allIn = allIn && ( m_Players[i]->folded() || ( m_Players[i]->getMoney() == 0 ) );
    }

    return allIn;
}

#pragma mark - MAIN

int main() {
    PokerDriver poker;
    for (int i = 0; i < 3; i++) {
        //enter ante loop
        poker.runAnte();
        if (poker.roundIsOver()) continue;
        //enter deal loop
        poker.runDeal();
        //enter first betting loop
        poker.runBetting(1);
        if (poker.roundIsOver()) continue;
        //enter card exchnage loop
        poker.runCardExchange();
        //enter second betting loop
        poker.runBetting(2);
        if (poker.roundIsOver()) continue;
        //enter showdown loop
        poker.finishRound();
        cout << "Round_SUCCESS" << endl;
    }

    poker.endGame("SUCCESS_ALL");
}
