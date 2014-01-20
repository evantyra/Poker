#include "Poker.h"

display GAME_DISPLAY;

Poker::Poker() :
    m_InitialPlayers(4),
    m_InitialMoney(10000),
    m_RoundCounter(1),
    m_PotMoney(0),
    bettingCycle(1),
    player0Frame(20, 16, 38, 7),
    player1Frame(0 ,  9, 38, 7),
    player2Frame(20,  1, 38, 7),
    player3Frame(40,  9, 38, 7),
    m_HumanPlayer(0, m_InitialMoney),
    m_AiPlayer_1(1, m_InitialMoney),
    m_AiPlayer_2(2, m_InitialMoney),
    m_AiPlayer_3(3, m_InitialMoney),
    m_Players()

{
    m_HumanPlayer.setFrame(&player0Frame);
    m_AiPlayer_1.setFrame(&player1Frame);
    m_AiPlayer_2.setFrame(&player2Frame);
    m_AiPlayer_3.setFrame(&player3Frame);

    m_Players.push_back(&m_AiPlayer_1);
    m_Players.push_back(&m_AiPlayer_2);
    m_Players.push_back(&m_AiPlayer_3);
    m_Players.push_back(&m_HumanPlayer);

    initializeDisplay();
}

Poker::~Poker() {}

#pragma mark - Display

void Poker::initializeDisplay() {
    updateGameInfo();
}

void Poker::setTopBannerText(string text) {
    GAME_DISPLAY.bannerTop(text);
}

void Poker::setBottomBannerText(string text) {
    GAME_DISPLAY.bannerBottom(text);
}

void Poker::removePlayer(int position) {
    Frame frame;

    switch (position) {
        case 0:
            frame = player0Frame;
            break;
        case 1:
            frame = player1Frame;
            break;
        case 2:
            frame = player2Frame;
            break;
        case 3:
            frame = player3Frame;
            break;
        default: return;
    }

    GAME_DISPLAY.eraseBox(frame.getX(), frame.getY(), frame.getWidth(), frame.getHeight());
}

void Poker::drawHand(Hand *hand, bool hidden, Frame *frame) {
    int x = frame->getX(), y = frame->getY(), w = frame->getWidth(), h = frame->getHeight();

    if (hidden) { //top player
        for (int i = 0; i < 5; i++) {
            GAME_DISPLAY.displayCard(x + 1 + i*7, y + 2, 0, 0, 0);
        }
    } else if (hand != NULL) { //display cards for human player
        Card *card;
        for (int i = 0; i < 5; i++) {
            card = hand->getCard(i);
            GAME_DISPLAY.displayCard(x + 1 + i*7, y + 2, card->getSuit() + 1, card->getNumber(), 0);
        }
    }
}

void Poker::updateHand(Hand *hand, Frame *frame) {
    if (hand != NULL) {
        GAME_DISPLAY.eraseBox(frame->getX(), frame->getY(), frame->getWidth(), frame->getHeight());
        drawHand(hand, false, frame);
    }
}

//called whenever any player money or pot changes, or when round round or style changes
void Poker::updateGameInfo() {
    stringstream bannerText;
    bannerText << bannerHeader << " || ";
    bannerText << "Me: $" << m_HumanPlayer.getMoney();
    bannerText << " | W: $" << m_AiPlayer_1.getMoney();
    bannerText << " | N: $" << m_AiPlayer_2.getMoney();
    bannerText << " | E: $" << m_AiPlayer_3.getMoney();
    bannerText << " | Pot: $" << m_PotMoney;
    setTopBannerText(bannerText.str());
}

#pragma mark - deque manipulate methods

void Poker::rotatePlayers() {
    Player *tempPlayer = m_Players.front();
    m_Players.pop_front();
    m_Players.push_back(tempPlayer);
}

void Poker::removeCurrentPlayer() {
    removePlayer(((Player *)m_Players.front())->getDisplayPosition());
    m_Players.pop_front();
}

#pragma mark - Game Play

void Poker::runAnte() {
    stringstream bannerText;
    bannerText << "Round " << m_RoundCounter << ": Ante";
    bannerHeader = bannerText.str();
    updateGameInfo();

    int a = ante();

    for (int i = 0; i < m_Players.size(); i++) {
        Player *player = m_Players.front();

        if (typeid(*player) == typeid(HumanPlayer)) {
            HumanPlayer *hPlayer = (HumanPlayer *) player;

            if (hPlayer->ante(a, GAME_DISPLAY) == Player::FOLD) { //didn't ante, remove human player from game
                endGame("No ante? You lose :(");
            }
        } else {
            AI *cPlayer = (AI *) player;
            if(cPlayer->ante(a, GAME_DISPLAY) == Player::FOLD) {
                removeCurrentPlayer();
                i--;
                continue;
            }
        }

        m_PotMoney += player->getMoneyInPot();
        updateGameInfo();

        rotatePlayers();
    }
}

void Poker::runDeal() {
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

        drawHand(NULL, true, m_Players[i]->getFrame());
    }

    updateHand(m_HumanPlayer.getHand(), &player0Frame);
}


void Poker::runBetting(int bettingCycle) {
    stringstream bannerText;
    bannerText << "Round " << m_RoundCounter << ": Betting Cycle " << bettingCycle;
    bannerHeader = bannerText.str();
    updateGameInfo();

    int bet, callCounter = 0, minBet;

    while (unfoldedPlayers() > 1) {
        Player *player = m_Players.front();
        minBet = minimumBet(player);

        if (player->folded()) {
            callCounter++;
        } else {
            bet = player->bet(minBet, GAME_DISPLAY);
            callCounter++;

            if (bet != Player::FOLD) {
                m_PotMoney += bet;
                updateGameInfo();

                if (bet > minBet) {
                    callCounter = 1;
                }
            } else {
                removePlayer(player->getDisplayPosition());
            }
        }

        if (callCounter >= unfoldedPlayers() || allPlayersAllIn())
            break;

        rotatePlayers();
    }
}

int Poker::unfoldedPlayers() {
    int unfolded = 0;
    
    for (int i = 0; i < m_Players.size(); i++) {
        unfolded += (int) !m_Players[i]->folded();
    }
    
    return unfolded;
}

void Poker::runCardExchange() {
    stringstream bannerText;
    bannerText << "Round " << m_RoundCounter << ": Betting Cycle " << bettingCycle;
    bannerHeader = bannerText.str();
    updateGameInfo();

    //bringHumanToFront();
    for (int i = 0; i < m_Players.size(); i++) {
        Player *player = m_Players.front();

        if (!player->folded()) {
            player->discard(GAME_DISPLAY);

            for (int j = 0; j < 5; j++) {
                if (player->getHand()->getCard(j)->isDiscarded()) {
                    m_Deck.discardCard(player->getHand()->exchange(m_Deck.drawCard(), j));
                }
            }

            if (typeid(*player) == typeid(HumanPlayer)) {
                updateHand(player->getHand(), player->getFrame());
            }
        }

        rotatePlayers();
    }
}

void Poker::runShowdown() {
    for (int i = 0; i < m_Players.size(); i++) {
        if (m_Players[i]->folded()) {
            removePlayer(m_Players[i]->getDisplayPosition());
        } else {
            updateHand(m_Players[i]->getHand(), m_Players[i]->getFrame());
        }
    }
}

bool Poker::roundIsOver() {
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
        setBottomBannerText("Round over. <Press c to continue>");
        finalizeRound();
        return true;
    }

    return false;
}

int Poker::getRemainingPotMoney(){
    int sum = 0;
    for(int i = 0; i < m_Players.size(); i++){
        sum += m_Players[i]->getMoneyInPot();
    }
    return sum;
}

bool Poker::finishRound() {

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

    string outcome = (&m_HumanPlayer != winner )?"You lost :(":"You Win :)";

    stringstream bannerText;
    bannerText << outcome << "; c: continue";
    setBottomBannerText(bannerText.str());

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

void Poker::finalizeRound() {
    for (int i = 0; i < m_Players.size(); i++) {
        m_Players[i]->setMoneyInPot(0);
    }

    bettingCycle++;

    m_PotMoney = 0;
    bannerHeader = "";
    updateGameInfo();

    int input;
    while (1) {
        input = GAME_DISPLAY.captureInput();
        if (input == 'c' || input == 'C') {
            break;
        }
    }

    Hand *hand;
    for (int i = 0; i < m_Players.size(); i++) {
        m_Players[i]->setFolded(false);
        removePlayer(m_Players[i]->getDisplayPosition());
        hand = m_Players[i]->getHand();

        for (int j = 0; j < 5; j++) {
            m_Deck.discardCard(hand->getCard(j));
        }
        //delete hands
    }
}

void Poker::endGame(string endReason) {
    int input;
    stringstream bannerText;
    bannerText << endReason << "; e:exit";
    setBottomBannerText(bannerText.str());

    while (1) {
        input = GAME_DISPLAY.captureInput();

        if (input == 'e' || input == 'E') {
            exit(0);
        }
    }
}

#pragma mark - Misc. Controls

int Poker::ante() {
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

int Poker::minimumBet(Player *player) {
    return ( maxSinglePlayerMoney() - player->getMoneyInPot() );
}

int Poker::maxSinglePlayerMoney() {
    return max( m_HumanPlayer.getMoneyInPot(), max( m_AiPlayer_1.getMoneyInPot(), max( m_AiPlayer_2.getMoneyInPot(), m_AiPlayer_3.getMoneyInPot() ) ) );
}

bool Poker::allPlayersAllIn() {
    bool allIn = true;
    for (int i = 0; i <  m_Players.size(); i++) {
        allIn = allIn && m_Players[i]->folded() || ( m_Players[i]->getMoney() == 0 );
    }

    return allIn;
}

#pragma mark - MAIN

int main() {
    Poker poker;
    while (poker.m_Players.size() > 1) {
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
        poker.runShowdown();
        poker.finishRound();
    }

    poker.endGame("You Win!!");
}
