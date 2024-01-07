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
// using std::vector;
// using std::map;
// using std::ofstream;

#define MINBET 25
#define RESHUFFLEPOINT 104
#define NUMDECKS 8
#define CYCLES 10000

int main() {
    auto start = chrono::high_resolution_clock::now();
    Dealer dealer(Dealer::SOFT_17);

    Shoe* shoe = new Shoe(NUMDECKS);
    shoe->shuffle();
    shoe->burnCard();
    
    Table table1(5, shoe, &dealer);
    
    Player player1(100, MINBET, Player::OPTIMAL_CHART, CYCLES, {0.0});
    Player player2(100, MINBET, Player::SOFT_17, CYCLES, {0.0});
    Player player3(100, MINBET, Player::HARD_17, CYCLES, {0.0});
    Player player4(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.6775});
    Player player5(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.685});

    // Player player1(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.675});
    // Player player2(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.6775});
    // Player player3(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.680});
    // Player player4(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.6825});
    // Player player5(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.685});

    // Player player1(100, MINBET, Player::OPTIMAL_CHART, CYCLES, {0.0});
    // Player player2(100, MINBET, Player::CARD_COUNT_STAND, CYCLES, {0.6});
    // Player player3(100, MINBET, Player::CARD_COUNT_STAND, CYCLES, {0.7});
    // Player player4(100, MINBET, Player::CARD_COUNT_STAND, CYCLES, {0.8});
    // Player player5(100, MINBET, Player::CARD_COUNT_STAND, CYCLES, {0.9});

    for(int c = 0; c < CYCLES; c++) {
        cout << endl << "CYCLE " << c + 1 << endl;

        //Reset Balance to 100
        player1.setBalance(100);
        player2.setBalance(100);
        player3.setBalance(100);
        player4.setBalance(100);
        player5.setBalance(100);

        //Re-Add Players to Table
        table1.addPlayer(&player1, 1);
        table1.addPlayer(&player2, 2);
        table1.addPlayer(&player3, 3);
        table1.addPlayer(&player4, 4);
        table1.addPlayer(&player5, 5);
        
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
            if(player5.getBalance() < MINBET || player5.getBalance() > 1000) {
                table1.removePlayer(5);
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

    // player1.writeDataToCSV("player1Games.csv");
    // player2.writeDataToCSV("player2Games.csv");
    // player3.writeDataToCSV("player3Games.csv");
    // player4.writeDataToCSV("player4Games.csv");
    // player5.writeDataToCSV("player5Games.csv");

    player1.averageData();
    player2.averageData();
    player3.averageData();
    player4.averageData();
    player5.averageData();

    player1.writeDataToCSV("player1Data.csv");
    player2.writeDataToCSV("player2Data.csv");
    player3.writeDataToCSV("player3Data.csv");
    player4.writeDataToCSV("player4Data.csv");
    player5.writeDataToCSV("player5Data.csv");

    auto stop2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::seconds>(stop2 - start2);
    int minutes2 = duration2.count() / 60;
    int seconds2 = duration2.count() % 60;
    cout << "Data Averaging Time: " << minutes2 << " M : " << seconds2 << " S" << endl;

    delete shoe;

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    int minutes = duration.count() / 60;
    int seconds = duration.count() % 60;
    cout << "Total Time: " << minutes << " M : " << seconds << " S" << endl;

}