#include <iostream>
#include <stdio.h>
#include "Deck.h"
#include "AI.h"

int main(int argc, char* argv[]) {

    Deck* d1 = new Deck();
    int argument1 = atoi(argv[1]);
    Player* player1 = new AI(1,argument1);
    
    int anteResult = argument1 / 5;

    if (anteResult ==  argument1 / 5)
    {
        cout << "Success" << endl;
    }
    else
    {
        cout << "Failure" << endl;
    }

    Card* c1;
    int cardsDrawn = atoi(argv[2]);

    for (int i = 0; i < cardsDrawn; i++)
    {
        c1 = d1->drawCard();
    }
    
    if (d1->cardsRemaining() == 52-cardsDrawn)
    {
        cout << "Success" << endl;
    }
    else
    {
        cout << "Failure" << endl;
    }
    
    d1->shuffle();

    if (d1->cardsRemaining() == 52)
    {
        cout << "Success" << endl;
    }
    else
    {
        cout << "Failure" << endl;
    }

    d1->discardCard(c1);
    
    if (d1->cardsDiscarded() == 1)
    {
        cout << "Success" << endl;
    }
    else
    {
        cout << "Failure" << endl;
    }
    
    d1->shuffle();

    if (d1->cardsDiscarded() == 0)
    {
        cout << "Success" << endl;
    }
    else
    {
        cout << "Failure" << endl;
    }
    
    player1->setHand(d1->dealHand());
    Hand* h1 = player1->getHand();

    for (int i = 0; i < 5; i++)
    {
        int isCardValid = h1->getCard(i)->getSuit() + h1->getCard(i)->getRank();
        if (isCardValid > 1)
        {
            cout << "Success" << endl;
        }
        else
        {
            cout << "Failure" << endl;
        }
    }

    d1->shuffle();

    player1->setHand(d1->dealHand());
    h1 = player1->getHand();

    for (int i = 0; i < 5; i++)
    {
        int isCardValid = h1->getCard(i)->getSuit() + h1->getCard(i)->getRank();
        if (isCardValid > 1)
        {
            cout << "Success" << endl;
        }
        else
        {
            cout << "Failure" << endl;
        }
    }
    
    return 0;
}
