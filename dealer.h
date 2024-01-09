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
        H,
        S
    };

    enum Strategy {
        SOFT_17,
        HARD_17,
    }; 

    //Constructors
    Dealer(Strategy strategy);
    ~Dealer();

    //Hand
    Hand* getHand();

    //Decision
    Dealer::Decision makeDecision();

    //Payments
    void payOut(Player* player);
    void collectBet(Player* player);

    //Visible Card
    void printVisibleCard();
    Card* getVisibleCard();
    

    private: 
    Strategy strategy;
    Hand* hand;     //Dealer only ever has one hand, can't split
};

#endif //DEALER_H