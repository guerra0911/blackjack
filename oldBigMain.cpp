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
#define CYCLES 1000
#define NUM_TABLES 1

int main() {
    auto start = chrono::high_resolution_clock::now();
    Dealer dealer1(Dealer::SOFT_17);
    Dealer dealer2(Dealer::SOFT_17);
    Dealer dealer3(Dealer::SOFT_17);
    Dealer dealer4(Dealer::SOFT_17);
    Dealer dealer5(Dealer::SOFT_17);

    Shoe* shoe1 = new Shoe(NUMDECKS);
    shoe1->shuffle();
    shoe1->burnCard();
    Shoe* shoe2 = new Shoe(NUMDECKS);
    shoe2->shuffle();
    shoe2->burnCard();
    Shoe* shoe3 = new Shoe(NUMDECKS);
    shoe3->shuffle();
    shoe3->burnCard();
    Shoe* shoe4 = new Shoe(NUMDECKS);
    shoe4->shuffle();
    shoe4->burnCard();
    Shoe* shoe5 = new Shoe(NUMDECKS);
    shoe5->shuffle();
    shoe5->burnCard();
    
    Table table1(5, shoe1, &dealer1);
    Table table2(5, shoe2, &dealer2);
    Table table3(5, shoe3, &dealer3);
    Table table4(5, shoe4, &dealer4);
    Table table5(5, shoe5, &dealer5);

    Player player1(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.604});
    Player player2(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.608});
    Player player3(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.612});
    Player player4(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.616});
    Player player5(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.620});

    Player player6(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.624});
    Player player7(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.628});
    Player player8(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.632});
    Player player9(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.636});
    Player player10(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.640});

    Player player11(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.644});
    Player player12(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.648});
    Player player13(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.652});
    Player player14(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.656});
    Player player15(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.660});

    Player player16(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.664});
    Player player17(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.668});
    Player player18(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.672});
    Player player19(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.676});
    Player player20(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.680});

    Player player21(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.684});
    Player player22(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.688});
    Player player23(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.692});
    Player player24(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.696});
    Player player25(100, MINBET, Player::CARD_COUNT_HIT, CYCLES, {0.7});

    for(int c = 0; c < CYCLES; c++) {
        cout << endl << "CYCLE " << c + 1 << endl;

        //Reset Balance to 100
        player1.setBalance(100);
        player2.setBalance(100);
        player3.setBalance(100);
        player4.setBalance(100);
        player5.setBalance(100);
        player6.setBalance(100);
        player7.setBalance(100);
        player8.setBalance(100);
        player9.setBalance(100);
        player10.setBalance(100);
        player11.setBalance(100);
        player12.setBalance(100);
        player13.setBalance(100);
        player14.setBalance(100);
        player15.setBalance(100);
        player16.setBalance(100);
        player17.setBalance(100);
        player18.setBalance(100);
        player19.setBalance(100);
        player20.setBalance(100);
        player21.setBalance(100);
        player22.setBalance(100);
        player23.setBalance(100);
        player24.setBalance(100);
        player25.setBalance(100);

        //Re-Add Players to Table
        table1.addPlayer(&player1, 1);
        table1.addPlayer(&player2, 2);
        table1.addPlayer(&player3, 3);
        table1.addPlayer(&player4, 4);
        table1.addPlayer(&player5, 5);
        table2.addPlayer(&player6, 1);
        table2.addPlayer(&player7, 2);
        table2.addPlayer(&player8, 3);
        table2.addPlayer(&player9, 4);
        table2.addPlayer(&player10, 5);
        table3.addPlayer(&player11, 1);
        table3.addPlayer(&player12, 2);
        table3.addPlayer(&player13, 3);
        table3.addPlayer(&player14, 4);
        table3.addPlayer(&player15, 5);
        table4.addPlayer(&player16, 1);
        table4.addPlayer(&player17, 2);
        table4.addPlayer(&player18, 3);
        table4.addPlayer(&player19, 4);
        table4.addPlayer(&player20, 5);
        table5.addPlayer(&player21, 1);
        table5.addPlayer(&player22, 2);
        table5.addPlayer(&player23, 3);
        table5.addPlayer(&player24, 4);
        table5.addPlayer(&player25, 5);

        
        //Add initial 100 Balance to Data
        table1.addAllData(c);
        table2.addAllData(c);
        table3.addAllData(c);
        table4.addAllData(c);
        table5.addAllData(c);


        while(table1.numPlayersAtTable() > 0) {  
            table1.playRound();
            table1.collectionsAndPayOuts();
            table1.addAllData(c);
            table1.clearAllHands();

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

            if(table1.cardsLeftAtTable() < RESHUFFLEPOINT) {        
                table1.reinitializeShoe();
            }
        }

        while(table2.numPlayersAtTable() > 0) {             
            table2.playRound();
            table2.collectionsAndPayOuts();
            table2.addAllData(c);
            table2.clearAllHands();

            if(player6.getBalance() < MINBET || player6.getBalance() > 1000) {
                table2.removePlayer(1);
            }
            if(player7.getBalance() < MINBET || player7.getBalance() > 1000) {
                table2.removePlayer(2);
            }
            if(player8.getBalance() < MINBET || player8.getBalance() > 1000) {
                table2.removePlayer(3);
            }
            if(player9.getBalance() < MINBET || player9.getBalance() > 1000) {
                table2.removePlayer(4);
            }
            if(player10.getBalance() < MINBET || player10.getBalance() > 1000) {
                table2.removePlayer(5);
            }

            if(table2.cardsLeftAtTable() < RESHUFFLEPOINT) {        
                table2.reinitializeShoe();
            }
        }

        while(table3.numPlayersAtTable() > 0) {   
            table3.playRound();
            table3.collectionsAndPayOuts();
            table3.addAllData(c);
            table3.clearAllHands();

            if(player11.getBalance() < MINBET || player11.getBalance() > 1000) {
                table3.removePlayer(1);
            }
            if(player12.getBalance() < MINBET || player12.getBalance() > 1000) {
                table3.removePlayer(2);
            }
            if(player13.getBalance() < MINBET || player13.getBalance() > 1000) {
                table3.removePlayer(3);
            }
            if(player14.getBalance() < MINBET || player14.getBalance() > 1000) {
                table3.removePlayer(4);
            }
            if(player15.getBalance() < MINBET || player15.getBalance() > 1000) {
                table3.removePlayer(5);
            }

            if(table3.cardsLeftAtTable() < RESHUFFLEPOINT) {       
                table3.reinitializeShoe();
            }
        }

        while(table4.numPlayersAtTable() > 0) {
            table4.playRound();
            table4.collectionsAndPayOuts();
            table4.addAllData(c);
            table4.clearAllHands();

            if(player16.getBalance() < MINBET || player16.getBalance() > 1000) {
                table4.removePlayer(1);
            }
            if(player17.getBalance() < MINBET || player17.getBalance() > 1000) {
                table4.removePlayer(2);
            }
            if(player18.getBalance() < MINBET || player18.getBalance() > 1000) {
                table4.removePlayer(3);
            }
            if(player19.getBalance() < MINBET || player19.getBalance() > 1000) {
                table4.removePlayer(4);
            }
            if(player20.getBalance() < MINBET || player20.getBalance() > 1000) {
                table4.removePlayer(5);
            }

            if(table4.cardsLeftAtTable() < RESHUFFLEPOINT) {        
                table4.reinitializeShoe();
            }
        }

        while(table5.numPlayersAtTable() > 0) {   
            table5.playRound();
            table5.collectionsAndPayOuts();
            table5.addAllData(c);
            table5.clearAllHands();

            if(player21.getBalance() < MINBET || player21.getBalance() > 1000) {
                table5.removePlayer(1);
            }
            if(player22.getBalance() < MINBET || player22.getBalance() > 1000) {
                table5.removePlayer(2);
            }
            if(player23.getBalance() < MINBET || player23.getBalance() > 1000) {
                table5.removePlayer(3);
            }
            if(player24.getBalance() < MINBET || player24.getBalance() > 1000) {
                table5.removePlayer(4);
            }
            if(player25.getBalance() < MINBET || player25.getBalance() > 1000) {
                table5.removePlayer(5);
            }

            if(table5.cardsLeftAtTable() < RESHUFFLEPOINT) {      
                table5.reinitializeShoe();
            }
        }

        //Reset Shoe after Full Cycle
        table1.reinitializeShoe();
        table2.reinitializeShoe();
        table3.reinitializeShoe();
        table4.reinitializeShoe();
        table5.reinitializeShoe();
    }

    auto stop1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::seconds>(stop1 - start);
    int minutes1 = duration1.count() / 60;
    int seconds1 = duration1.count() % 60;
    cout << "Simulation Time: " << minutes1 << " M :" << seconds1 << " S" << endl;

    auto start2 = chrono::high_resolution_clock::now();

    player1.averageData();
    player2.averageData();
    player3.averageData();
    player4.averageData();
    player5.averageData();
    player6.averageData();
    player7.averageData();
    player8.averageData();
    player9.averageData();
    player10.averageData();
    player11.averageData();
    player12.averageData();
    player13.averageData();
    player14.averageData();
    player15.averageData();
    player16.averageData();
    player17.averageData();
    player18.averageData();
    player19.averageData();
    player20.averageData();
    player21.averageData();
    player22.averageData();
    player23.averageData();
    player24.averageData();
    player25.averageData();

    player1.writeDataToCSV("player1Data.csv");
    player2.writeDataToCSV("player2Data.csv");
    player3.writeDataToCSV("player3Data.csv");
    player4.writeDataToCSV("player4Data.csv");
    player5.writeDataToCSV("player5Data.csv");
    player6.writeDataToCSV("player6Data.csv");
    player7.writeDataToCSV("player7Data.csv");
    player8.writeDataToCSV("player8Data.csv");
    player9.writeDataToCSV("player9Data.csv");
    player10.writeDataToCSV("player10Data.csv");
    player11.writeDataToCSV("player11Data.csv");
    player12.writeDataToCSV("player12Data.csv");
    player13.writeDataToCSV("player13Data.csv");
    player14.writeDataToCSV("player14Data.csv");
    player15.writeDataToCSV("player15Data.csv");
    player16.writeDataToCSV("player16Data.csv");
    player17.writeDataToCSV("player17Data.csv");
    player18.writeDataToCSV("player18Data.csv");
    player19.writeDataToCSV("player19Data.csv");
    player20.writeDataToCSV("player20Data.csv");
    player21.writeDataToCSV("player21Data.csv");
    player22.writeDataToCSV("player22Data.csv");
    player23.writeDataToCSV("player23Data.csv");
    player24.writeDataToCSV("player24Data.csv");
    player25.writeDataToCSV("player25Data.csv");

    auto stop2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::seconds>(stop2 - start2);
    int minutes2 = duration2.count() / 60;
    int seconds2 = duration2.count() % 60;
    cout << "Data Averaging Time: " << minutes2 << " M : " << seconds2 << " S" << endl;

    delete shoe1;
    delete shoe2;
    delete shoe3;
    delete shoe4;
    delete shoe5;

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    int minutes = duration.count() / 60;
    int seconds = duration.count() % 60;
    cout << "Total Time: " << minutes << " M : " << seconds << " S" << endl;

}