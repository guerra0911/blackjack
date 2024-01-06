#ifndef PLAYER_H
#define PLAYER_H

//#include "card.h"
#include "hand.h"
#include <vector>
#include <string>
#include <fstream>

using std::vector;
using std::ofstream;

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
    Player(float initialBalance, float initialBet, Strategy strategy, int cycles);
    ~Player();

    //Balance
    float getBalance();
    void setBalance(float newBal);
    void increaseBalance(float amount);
    void decreaseBalance(float amount);

    //Bet
    float getBet();
    void placeBet(float amount);

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

    //Data
    void addData(int round);
    void averageData();
    void printData();
    void writeDataToCSV(const string& filename);
    

    private:
    float balance;
    float bet;
    int tablePos;

    Strategy strategy;
    vector<Hand*> hands;
    vector<vector<float>> data;

};

#endif //PLAYER_H