#ifndef PLAYER_H
#define PLAYER_H

//#include "card.h"
#include "hand.h"
#include <vector>
#include <string>

using std::vector;

class Player {
    public:

    enum Decision {
        H,  // Hit
        S,  // Stand
        P,  // Split
        RH, // Surrender if allowed, otherwise hit
        DH, // Double if allowed, otherwise hit
        DS  // Double if allowed, otherwise stand
    };


    enum Strategy {
        SOFT_17,
        HARD_17,
        OPTIMAL_CHART
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
    Player::Decision makeDecision(Hand* hand, int dealerCardVal);

    //Table
    int getTablePos();
    void setTablePos(int position);

    //Optimal Chart
    static vector<vector<Player::Decision>> optimalChart;  
    Player::Decision opChart(Hand* hand, int dealerCardVal);
    

    private:
    int balance;
    int bet;
    int tablePos;

    Strategy strategy;
    vector<Hand*> hands;

};

#endif //PLAYER_H