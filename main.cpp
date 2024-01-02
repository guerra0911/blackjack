#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include "card.h"
#include "shoe.h"
#include "player.h"
#include "dealer.h"
#include "table.h"

using namespace std;
using std::vector;
using std::map;

#define MINBET 25
#define RESHUFFLEPOINT 104
#define NUMDECKS 8

int main() {
    Dealer dealer(Dealer::SOFT_17);

    Shoe* shoe = new Shoe(NUMDECKS);
    shoe->shuffle();
    shoe->burnCard();
    
    Table table1(5, shoe, &dealer);
    
    Player player1(100, MINBET, Player::OPTIMAL_CHART);
    Player player2(100, MINBET, Player::SOFT_17);
    Player player3(100, MINBET, Player::HARD_17);

    table1.addPlayer(&player1, 1);
    table1.addPlayer(&player2, 2);
    table1.addPlayer(&player3, 3);

    int cardsDealt = 0;
    
    while(table1.numPlayersAtTable() > 0) {
        table1.playRound();
        table1.collectionsAndPayOuts();
        table1.clearAllHands();

        if(player1.getBalance() < MINBET) {
            table1.removePlayer(1);
        }
        if(player2.getBalance() < MINBET) {
            table1.removePlayer(2);
        }
        if(player3.getBalance() < MINBET) {
            table1.removePlayer(3);
        }

        

        if(shoe->cardsLeft() < RESHUFFLEPOINT) {      //If Shoe is Depleted past Shuffle Point

            shoe->reinitialize();
            shoe->shuffle();
            shoe->burnCard();
            cout << endl << "Shoe Reinitialized" << endl;
        }
        cout << endl;
    }

    cout << table1.numPlayersAtTable() << endl;
    delete shoe;

}