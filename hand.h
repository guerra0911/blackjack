#ifndef HAND_H
#define HAND_H

#include "card.h"
#include <vector>

using std::vector;

class Hand {
    public:
    //Constructors
    Hand();
    ~Hand();

    //Hand
    void addCardToHand(Card* card);
    void removeCardFromHand(int cardIndex);
    void clearHand();
    int getHandValue();
    Card* getCard(int cardIndex);
    

    //Actions
    bool isBust();
    bool isBlackJack();
    bool isPairAces();

    //Print
    void printHand();


    private:
    vector<Card*> hand;
};

#endif //HAND_H