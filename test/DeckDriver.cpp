#include <iostream>
#include "Deck.h"
#include "AI.h"

int main(int argc, char* argv[]) {

    Deck* d1 = new Deck();
    Player* player1 = new AI(1,20000);
    display display1;
    
    int betResult = player1->bet(5000, display1);

    if (betResult == 5000)
    {
        cout << "Bet: " << betResult << endl;
        cout << "Successful bet. " << player1->getMoney() << " remaining." << endl;
    }
    else
    {
        cout << "Unsuccessful. " << player1->getMoney() << " remaining." << endl;
    }

    int anteResult = player1->ante(1000);

    if (anteResult ==  1000)
    {
        cout << "Ante: " << anteResult << endl;
        cout << "Successful ante. " << player1->getMoney() << " remaining." << endl;
    }

    else
    {
        cout << "Unsuccessful. " << player1->getMoney() << " remaining." << endl;
    }

    Card* c1 = d1->drawCard();
    Card* c2 = d1->drawCard();
    Card* c3 = d1->drawCard();
    Card* c4 = d1->drawCard();
    Card* c5 = d1->drawCard();

    if (d1->cardsRemaining() == 47)
    {
        cout << "Five cards drawn successfully." << endl;
    }
    
    d1->shuffle();

    if (d1->cardsRemaining() == 52)
    {
        cout << "Deck shuffled successfully." << endl;
    }
    
    return 0;
}
