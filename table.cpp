#include "table.h"
#include "hand.h"
#include "card.h"
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
        shoe->dealToPlayer(pair.second,0);      //Index 0 = First Initial Hand
    }

    //Deal 1st Card (HIDDEN) to Dealer
    shoe->dealToDealer(dealer);

    //Deal 2nd Card to Each Player
    for(auto& pair : players) {
        shoe->dealToPlayer(pair.second,0);      //Index 0 = First Initial Hand
        (pair.second->getHand(0))->printHand();      
    }

    //Deal 2nd Card (VISIBLE) to Dealer
    shoe->dealToDealer(dealer);
    dealer->printVisibleCard();



    //For Each Player, Deal Until Bust, BlackJack or Stand
    for(auto& pair : players) {  
        Player* player = pair.second;  
        int handIndex = 0;

        //For Each Hand   in player object, vector<vector<Card*>>
        /*      */
        //Retrieve Decision() (Hit, Stand, Split, Double, Surrender) Based ON OPTIMAL TABLE IMPLEMENTATION, this just returns which enumeration based on OPTIMAL TABLE, no functionality

        //The actual functionality is below, based on if statements = to which enumeration, the carry out the following, until players turn is done
        //if HIT -> hit()
        //if STAND -> stand()
        //if SURRENDER -> surrender()
        //if DOUBLE -> double()
        //if SPLIT -> split()
        for(auto& hand : player->getHands()) {

            while(!hand->isBust() && !hand->isBlackJack() && !(player->makeDecision(hand) == player->STAND)) {
                shoe->dealToPlayer(player, handIndex);
                hand->printHand();
            }

            if(hand->isBust()) {
                cout << "Player " << player->getTablePos() << " Busts!" << endl;                           
            }

            if(hand->isBlackJack()) {  
                cout << "Player " << player->getTablePos() << " has BlackJack!" << endl;                                          
            }

            ++handIndex;
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
    for(auto& pair : players) {         //For Each Player
        Player* player = pair.second;

        for(auto& hand : player->getHands()) {  //For Each Hand Player Has
            // Player busts or has less points than dealer (who didn't bust)
            if(hand->isBust() || (hand->getHandValue() < dealer->getHandValue() && !dealer->isBust())) {
                player->decreaseBalance(player->getBet());
                cout << "Player " << player->getTablePos() << " Loses! New Balance = " << player->getBalance() << endl; 

            // Player has more points than dealer
            } else if((hand->getHandValue() > dealer->getHandValue()) || !hand->isBust() && dealer->isBust()) {

                // Player has a blackjack
                if(hand->isBlackJack()) {
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
}

void Table::clearAllHands() {
    dealer->clearHand();
    for(auto& pair : players) {                         //For Each Player
        (pair.second)->clearAllHands();               //Clear All their Hands
    }
}