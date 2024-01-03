#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>

#include "card.h"
#include "shoe.h"
#include "player.h"
#include "dealer.h"
#include "table.h"

using namespace std;
using std::vector;
using std::map;
using std::ofstream;

#define MINBET 25
#define RESHUFFLEPOINT 104
#define NUMDECKS 8
#define CYCLES 1000

int main() {
    Dealer dealer(Dealer::SOFT_17);

    Shoe* shoe = new Shoe(NUMDECKS);
    shoe->shuffle();
    shoe->burnCard();
    
    Table table1(5, shoe, &dealer);
    
    Player player1(100, MINBET, Player::OPTIMAL_CHART, CYCLES);
    Player player2(100, MINBET, Player::SOFT_17, CYCLES);
    Player player3(100, MINBET, Player::HARD_17, CYCLES);

    for(int c = 0; c < CYCLES; c++) {
        
        //Reset Balance to 100
        player1.setBalance(100);
        player2.setBalance(100);
        player3.setBalance(100);

        //Re-Add Players to Table
        table1.addPlayer(&player1, 1);
        table1.addPlayer(&player2, 2);
        table1.addPlayer(&player3, 3);
        
        //Add initial 100 Balance to Data
        table1.addAllData(c);


        while(table1.numPlayersAtTable() > 0) {             //Until Table is Empty
            table1.playRound();
            table1.collectionsAndPayOuts();
            table1.addAllData(c);
            table1.clearAllHands();

            //table1.checkPlayers();
            if(player1.getBalance() < MINBET || player1.getBalance() > 1000) {
                table1.removePlayer(1);
            }
            if(player2.getBalance() < MINBET || player2.getBalance() > 1000) {
                table1.removePlayer(2);
            }
            if(player3.getBalance() < MINBET || player3.getBalance() > 1000) {
                table1.removePlayer(3);
            }

            //table1.checkShoe();
            if(shoe->cardsLeft() < RESHUFFLEPOINT) {        //If Shoe is Depleted past Shuffle Point
                shoe->reinitialize();
                shoe->shuffle();
                shoe->burnCard();
                //cout << endl << "Shoe Reinitialized" << endl;
            }
        }
        cout << endl << "CYCLE " << c + 1<< endl;
    }

    //player1.printData();
    //player2.printData();
    //player3.printData();

    player1.writeDataToCSV("player1.csv");
    player2.writeDataToCSV("player2.csv");
    player3.writeDataToCSV("player3.csv");


    //cout << table1.numPlayersAtTable() << endl;
    delete shoe;

}