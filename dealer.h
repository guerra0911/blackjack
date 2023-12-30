#ifndef DEALER_H
#define DEALER_H

#include "card.h"
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
    void addCardToHand(Card* card);
    void clearHand();
    int getHandValue();

    //Decision
    Dealer::Decision makeDecision();

    //Payments
    void payOut(Player* player);
    void collectBet(Player* player);


    private:
    vector<Card*> hand;  //Copies of Card b/c hand is small

};

#endif //DEALER_H