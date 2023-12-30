#ifndef TABLE_H
#define TABLE_H

#include "player.h"
#include "dealer.h"
#include "shoe.h"
#include <vector>
#include <map>

using std::vector;
using std::map;

class Table {
    public:
    
    //Constructors
    Table(int numSeats);
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

    //Play
    void playRound(Shoe* shoe);
    void clearAllHands();
    void collectionsAndPayOuts(); 


    private:
    int numSeats;                   //Seats at the table
    map<int, Player*> players;      //.first = Position, .second = Player
    Dealer* dealer;
};

#endif //TABLE_H