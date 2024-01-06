#ifndef TABLE_H
#define TABLE_H

#include "player.h"
#include "dealer.h"
#include "shoe.h"
#include "hand.h"
#include <vector>
#include <map>

using std::vector;
using std::map;

class Table {
    public:
    
    //Constructors
    Table(int numSeats, Shoe* shoe, Dealer* dealer);
    ~Table();

    //Seats
    int numAvailableSeats();
    int getNumSeats();
    int numPlayersAtTable();

    //Dealer
    void setDealer(Dealer* tableDealer);

    //Players
    void addPlayer(Player* player, int position);
    void removePlayer(int position);
    Player* playerAtPos(int position);

    //Shoe
    void reinitializeShoe();
    int cardsLeftAtTable();

    //Play
    void eval(Player* player, int handIndex, int dealerCardVal);
    void playRound();
    void collectionsAndPayOuts(); 
    void clearAllHands();
    void addAllData(int round);
    void dealToPlayer(Player* player, int handIndex);
    void dealToDealer();
    void revealHiddenDealerCard();


    private:
    int numSeats;                   //Seats at the table
    map<int, Player*> players;      //.first = Position, .second = Player
    Dealer* dealer;
    Shoe* shoe;     
};

#endif //TABLE_H