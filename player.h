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
    Player(int initialBalance);
    ~Player();

    //Balance
    int getBalance();
    void increaseBalance(int amount);
    void decreaseBalance(int amount);

    //Bet
    int getBet();
    int placeBet(int amount);

    //Hand
    void addCardToHand(Card* card);
    void clearHand();
    int getHandValue();

    //Decision
    Player::Decision makeDecision();

    //Table
    int getTablePos();

    
    private:
    int balance;
    int bet;
    int tablePos;
    vector<Card*> hand;
};