#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include <chrono>

#include "card.h"
#include "shoe.h"
#include "player.h"
#include "dealer.h"
#include "table.h"

using namespace std;

#define MINBET 25
#define RESHUFFLEPOINT 104
#define NUMDECKS 8
#define CYCLES 900000
#define NUM_TABLES 1

int main() {
    auto start = chrono::high_resolution_clock::now();
    Dealer dealer1(Dealer::SOFT_17);

    Shoe* shoe1 = new Shoe(NUMDECKS);
    shoe1->shuffle();
    shoe1->burnCard();
    
    Table table1(5, shoe1, &dealer1);

    Player player1(100, MINBET, Player::CARD_COUNT, CYCLES);
    Player player2(100, MINBET, Player::OPTIMAL_CHART, CYCLES);
    Player player3(100, MINBET, Player::HARD_17, CYCLES);
    Player player4(100, MINBET, Player::SOFT_17, CYCLES);

    for(int c = 0; c < CYCLES; c++) {
        cout << endl << "CYCLE " << c + 1 << endl;

        //Reset Balance to 100
        player1.setBalance(100);
        player2.setBalance(100);
        player3.setBalance(100);
        player4.setBalance(100);

        //Re-Add Players to Table
        table1.addPlayer(&player1, 1);
        table1.addPlayer(&player2, 2);
        table1.addPlayer(&player3, 3);
        table1.addPlayer(&player4, 4);
    
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
            if(player4.getBalance() < MINBET || player4.getBalance() > 1000) {
                table1.removePlayer(4);
            }

            //table1.checkShoe();
            if(table1.cardsLeftAtTable() < RESHUFFLEPOINT) {        //If Shoe is Depleted past Shuffle Point
                table1.reinitializeShoe();
            }
        }

        //Reset Shoe after Full Cycle
        table1.reinitializeShoe();
    }

    auto stop1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::seconds>(stop1 - start);
    int minutes1 = duration1.count() / 60;
    int seconds1 = duration1.count() % 60;
    cout << "Simulation Time: " << minutes1 << " M :" << seconds1 << " S" << endl;

    auto start2 = chrono::high_resolution_clock::now();

    player1.calcWinsLosses();
    player2.calcWinsLosses();
    player3.calcWinsLosses();
    player4.calcWinsLosses();

    player1.writeWinsLosses("player1Results.csv");
    player2.writeWinsLosses("player2Results.csv");
    player3.writeWinsLosses("player3Results.csv");
    player4.writeWinsLosses("player4Results.csv");

    player1.averageData();
    player2.averageData();
    player3.averageData();
    player4.averageData();

    player1.writeDataToCSV("player1Data.csv");
    player2.writeDataToCSV("player2Data.csv");
    player3.writeDataToCSV("player3Data.csv");
    player4.writeDataToCSV("player4Data.csv");

    auto stop2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::seconds>(stop2 - start2);
    int minutes2 = duration2.count() / 60;
    int seconds2 = duration2.count() % 60;
    cout << "Data Averaging Time: " << minutes2 << " M : " << seconds2 << " S" << endl;

    delete shoe1;

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    int minutes = duration.count() / 60;
    int seconds = duration.count() % 60;
    cout << "Total Time: " << minutes << " M : " << seconds << " S" << endl;
}