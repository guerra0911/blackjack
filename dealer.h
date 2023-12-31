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
    //void addCardToHand(Card* card);
    //void clearHand();
    //int getHandValue();
    Hand* getHand();

    //Decision
    Dealer::Decision makeDecision();

    //Payments
    void payOut(Player* player);
    void collectBet(Player* player);

    //Actions
    //bool isBust();
    //bool isBlackJack();

    //Print
    void printVisibleCard();
    //void printHand();

    private:
    //vector<Card*> hand;  
    Hand* hand;     //Dealer only ever has one hand, can't split
};

#endif //DEALER_H