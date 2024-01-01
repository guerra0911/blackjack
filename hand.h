#ifndef HAND_H
#define HAND_H

#include "card.h"
#include <vector>

using std::vector;

class Hand {
    public:

    enum BetType{
        REGULAR,
        DOUBLE,
        SURRENDER
    };

    //Constructors
    Hand();
    ~Hand();

    //Hand
    void addCardToHand(Card* card);
    void removeCardFromHand(int cardIndex);
    void clearHand();
    int getHandValue();
    Card* getCard(int cardIndex);

    //Status (Whether Hand is Split, Doubled, or Surrendered)
    void setBetType(Hand::BetType status);
    Hand::BetType getBetType();

    //Actions
    bool isBust();
    bool isBlackJack();
    bool isPairAces();
    bool hasAce();

    //Print
    void printHand();


    private:
    BetType betType;
    vector<Card*> hand;
};

#endif //HAND_H