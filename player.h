#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "hand.h"
#include <vector>
#include <string>
#include <fstream>
#include <map>

using std::vector;
using std::ofstream;
using std::map;

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
        OPTIMAL_CHART,
        CARD_COUNT
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
    void calcWinsLosses(int minBet, int maxOut);
    void averageData();
    void printData();
    void writeWinsLosses(const string& filename);
    void writeDataToCSV(const string& filename);

    //Card Counting
    int getCardCount(Card::Rank rank);      //Get Count of Rank
    void reinitializeCardCount();           //Reset Card Count
    void decCardCount(Card* card);          //Decrease Card Count by 1
    void printCardCount();
    float probGet(int desiredHandVal, Hand* hand);
    float probNotBust(Hand* hand);
    float probBust(Hand* hand);
    float probBlackJack(Hand* hand);
    

    private:
    float balance;
    float bet;
    int tablePos;
    float totalCardsCounted;
    int wins;
    int losses;

    Strategy strategy;
    vector<Hand*> hands;                
    vector<vector<float>> data;         //Average Value of Turn & Turn Freq
    map<Card::Rank, int> cardCount;     //Keeps count of cards in shoe

};

#endif //PLAYER_H