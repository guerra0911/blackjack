#ifndef PLAYER_H
#define PLAYER_H

//#include "card.h"
#include "hand.h"
#include <vector>

using std::vector;

class Player {
    public:

    enum Decision {
        HIT,
        STAND,
        SPLIT,
        DOUBLE,
        SURRENDER
    };

    enum Strategy {
        SOFT_17,
        HARD_17
        //OPTIMAL_CHART,
        //CARD_COUNT   
    };

    //Constructors
    Player(int initialBalance, int initialBet, Strategy strategy);
    ~Player();

    //Balance
    int getBalance();
    void increaseBalance(int amount);
    void decreaseBalance(int amount);

    //Bet
    int getBet();
    void placeBet(int amount);

    //Hand
    Hand* getHand(int handIndex);
    vector<Hand*> getHands();
    void clearAllHands();
    void split(int handIndex);
    
    
    //Decision
    Player::Decision makeDecision(Hand* hand);

    //Table
    int getTablePos();
    void setTablePos(int position);

    

    
    private:
    int balance;
    int bet;
    int tablePos;
    Strategy strategy;
    vector<Hand*> hands;
};

#endif //PLAYER_H