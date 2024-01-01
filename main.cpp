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
#define SHUFFLEPOINT 104

int main() {
    Dealer dealer(Dealer::SOFT_17);

    Shoe* shoe = new Shoe(8);
    shoe->shuffle();
    shoe->burnCard();
    
    Table table1(5, shoe, &dealer);
    
    Player player1(100, MINBET, Player::OPTIMAL_CHART);

    table1.addPlayer(&player1, 1);
    
    while(player1.getBalance() > MINBET) {
        table1.playRound();
        table1.collectionsAndPayOuts();
        table1.clearAllHands();

        if(shoe->cardsLeft() < SHUFFLEPOINT) {      //If Shoe is Depleted past Shuffle Point
            shoe->reinitialize();
            shoe->shuffle();
            shoe->burnCard();

        }
        cout << endl;
    }

    table1.removePlayer(player1.getTablePos());
    delete shoe;

}