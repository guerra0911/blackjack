#ifndef DEALER_H
#define DEALER_H

#include "card.h"
#include "hand.h"
#include "player.h"

#include <vector>

using std::vector;

class Dealer {
    public:

    enum Decision {
        HIT,
        STAND
    };

    //Constructors
    Dealer();
    ~Dealer();

    //Hand
    Hand* getHand();

    //Decision
    Dealer::Decision makeDecision();

    //Payments
    void payOut(Player* player);
    void collectBet(Player* player);

    //Print
    void printVisibleCard();
    

    private: 
    Hand* hand;     //Dealer only ever has one hand, can't split
};

#endif //DEALER_H