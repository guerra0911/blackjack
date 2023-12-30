#include "table.h"
#include <iostream>

using namespace std;

//Constructors
Table::Table() {}

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
    }

    //Deal 2nd Card (VISIBLE) to Dealer
    shoe->dealToDealer(dealer);

    //For Each Player, Deal Until Bust, BlackJack or Stand
    for(auto& pair : players) {         

        if((pair.second)->isBust()) {
            continue;                           
        }

        if((pair.second)->isBlackJack()) {                     
            continue;                       
        }

        while(!((pair.second)->isBust()) || !((pair.second)->isBlackJack()) || !((pair.second)->makeDecision() == (pair.second)->STAND)) {
            shoe->dealToPlayer((pair.second));
        }
    }

    //Deal the Dealer Until Bust, BlackJack or Stand
    while(!(dealer->isBust()) || !(dealer->isBlackJack()) || !(dealer->makeDecision() == dealer->STAND)) {
        shoe->dealToDealer(dealer);
    }
}

void Table::collectionsAndPayOuts() {
    for(auto& pair : players) {
        //If Player Bust or Less Than Dealer = LOSE
        if((pair.second)->isBust() || (pair.second)->getHandValue() < dealer->getHandValue()) {
            (pair.second)->decreaseBalance((pair.second)->getBet());

        //If Player Greater Than Dealer = WIN
        } else if((pair.second)->getHandValue() > dealer->getHandValue()) {
            (pair.second)->increaseBalance((pair.second)->getBet());
        }

        //If Player Hand = Dealer Hand = DRAW (Nothing Happens)
    }
}