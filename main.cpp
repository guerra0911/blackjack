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

int main() {
    Table table1;

    Shoe shoe(3);
    shoe.shuffle();

    Dealer dealer;
    Player player1(100);
    Player player2(200);
    Player player3(300);
    Player player4(400);
    Player player5(500);

    table1.setDealer(&dealer);
    table1.addPlayer(&player1, 1);
    table1.addPlayer(&player2, 2);
    table1.addPlayer(&player3, 3);
    table1.addPlayer(&player4, 4);
    table1.addPlayer(&player5, 5);

}