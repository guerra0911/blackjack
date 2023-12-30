#include "table.h"
#include <iostream>

using namespace std;

//Constructors
Table::Table(int numSeats) : numSeats(numSeats) {}

Table::~Table() {}


//Seats
int Table::numAvailableSeats() {
    return numSeats - players.size();
}

int Table::getNumSeats() {
    return numSeats;
}

int Table::numPlayersAtTable() {
    return players.size();
}


//Dealer
void Table::setDealer(Dealer* tableDealer) {
    dealer = tableDealer;
}


//Players
void Table::addPlayer(Player* player, int position) {
    if(numAvailableSeats() == 0) {
        cout << "No Available Seats at this Table" << endl;
        return;
    }

    if (players.find(position) != players.end()) {
        cout << "This seat position is occupied, try a different seat" << endl;
        return;
    }

    players[position] = player;     //Assign specific player to specific position in table map

    player->setTablePos(position);
    
}

void Table::removePlayer(int position) {
    delete players[position];       //Delete the Player from existence
    players.erase(position);        //Erase them from the map
}

Player* Table::playerAtPos(int position) {
    return players[position];
}


//Play
void Table::playRound(Shoe* shoe) {

    //Deal 1st Card to Each Player
    for(auto& pair : players) {
        shoe->dealToPlayer(pair.second);
    }

    //Deal 1st Card (HIDDEN) to Dealer
    shoe->dealToDealer(dealer);

    //Deal 2nd Card to Each Player
    for(auto& pair : players) {
        shoe->dealToPlayer(pair.second);
        (pair.second)->printHand();

    }

    //Deal 2nd Card (VISIBLE) to Dealer
    shoe->dealToDealer(dealer);
    dealer->printVisibleCard();

    //For Each Player, Deal Until Bust, BlackJack or Stand
    for(auto& pair : players) {         

        while(!((pair.second)->isBust()) && !((pair.second)->isBlackJack()) && !((pair.second)->makeDecision() == (pair.second)->STAND)) {
            shoe->dealToPlayer((pair.second));
            (pair.second)->printHand();
        }

        if((pair.second)->isBust()) {
            cout << "Player " << (pair.second)->getTablePos() << " Busts!" << endl;                           
        }

        if((pair.second)->isBlackJack()) {  
            cout << "Player " << (pair.second)->getTablePos() << " has BlackJack!" << endl;                                          
        }
    }

    
    //Deal the Dealer Until Bust, BlackJack or Stand
    dealer->printHand();
    while(!(dealer->isBust()) && !(dealer->isBlackJack()) && !(dealer->makeDecision() == dealer->STAND)) {
        shoe->dealToDealer(dealer);
        dealer->printHand();
    }

    if(dealer->isBust()) {
        cout << "Dealer Busts!" << endl;                           
    }

    if(dealer->isBlackJack()) {  
        cout << "Dealer has BlackJack!" << endl;                                          
    }
}

void Table::collectionsAndPayOuts() {
    for(auto& pair : players) {
        Player* player = pair.second;

        // Player busts or has less points than dealer (who didn't bust)
        if(player->isBust() || (player->getHandValue() < dealer->getHandValue() && !dealer->isBust())) {
            player->decreaseBalance(player->getBet());
            cout << "Player " << player->getTablePos() << " Loses! New Balance = " << player->getBalance() << endl; 

        // Player has more points than dealer
        } else if(player->getHandValue() > dealer->getHandValue()) {

            // Player has a blackjack
            if(player->isBlackJack()) {
                player->increaseBalance(1.5 * player->getBet());  

            // Player wins but doesn't have a blackjack
            } else {
                player->increaseBalance(player->getBet());        
            }
            cout << "Player " << player->getTablePos() << " Wins! New Balance = " << player->getBalance() << endl;

        // Player and dealer have the same points
        } else {
            cout << "Player " << player->getTablePos() << " Draws." << endl;
        }
    }
}

void Table::clearAllHands() {
    dealer->clearHand();
    for(auto& pair : players) {         
        (pair.second)->clearHand();
    }
}