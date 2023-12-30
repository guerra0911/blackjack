#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include <vector>

using std::vector;

class Player {
    public:

    enum Decision {
        HIT,
        STAND
    };

    //Constructors
    Player(int initialBalance, int initialBet);
    ~Player();

    //Balance
    int getBalance();
    void increaseBalance(int amount);
    void decreaseBalance(int amount);

    //Bet
    int getBet();
    void placeBet(int amount);

    //Hand
    void addCardToHand(Card* card);
    void clearHand();
    int getHandValue();

    //Decision
    Player::Decision makeDecision();

    //Table
    int getTablePos();
    void setTablePos(int position);

    //Actions
    bool isBust();
    bool isBlackJack();

    //Print
    void printHand();

    
    private:
    int balance;
    int bet;
    int tablePos;
    vector<Card*> hand;
};

#endif //PLAYER_H