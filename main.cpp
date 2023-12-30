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

void playRound(Table* table, Shoe* shoe) {
    
}

int main() {
    Table table1;

    Shoe* shoe = new Shoe(3);
    shoe->shuffle();

    Dealer dealer;
    Player player1(100);

    table1.setDealer(&dealer);
    table1.addPlayer(&player1, 1);
    
    table1.playRound(shoe);
    table1.collectionsAndPayOuts();

    delete shoe;

}