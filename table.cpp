#include "table.h"
#include "hand.h"
#include "card.h"
#include <iostream>

using namespace std;

//Constructors
Table::Table(int numSeats, Shoe* shoe, Dealer* dealer) : numSeats(numSeats), shoe(shoe), dealer(dealer) {}

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
void Table::eval(Player* player, int handIndex) {
    Hand* playerHand = player->getHand(handIndex);

    //While Player hasnt Busted, Hasn't Hit BlackJack, Hasn't Decided to Stand, Hasn't gone over 21, keep asking to play
    while(!playerHand->isBust() && !playerHand->isBlackJack() && !(player->makeDecision(playerHand) == player->STAND) && playerHand->getHandValue() < 22) {
        
        //HIT
        if(player->makeDecision(playerHand) == player->HIT) {
            shoe->dealToPlayer(player, handIndex);
            playerHand->printHand();
            playerHand->setBetType(Hand::REGULAR);

        //DOUBLE
        } else if(player->makeDecision(playerHand) == player->DOUBLE) {
            shoe->dealToPlayer(player, handIndex);
            playerHand->printHand();
            playerHand->setBetType(Hand::DOUBLE);      //Indicate 2x Payout
            break;
        
        //SURRENDER
        } else if(player->makeDecision(playerHand) == player->SURRENDER) {
            playerHand->setBetType(Hand::SURRENDER);   //Indicate 0.5x Payout      
            break;
        }
    }

    if(playerHand->isBust()) {
        cout << "Player " << player->getTablePos() << " Busts!" << endl;                           
    }

    if(playerHand->isBlackJack()) {  
        cout << "Player " << player->getTablePos() << " has BlackJack!" << endl;                                          
    }
}

void Table::playRound() {
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
        int splits = 0;

        //If Player Decided to Split
        if(player->makeDecision(player->getHand(handIndex)) == player->SPLIT) {
            
            //Split there First Hand    < H1 >  ->  < H11, H12>
            player->split(handIndex);
            splits++;

            //Deal Next Card to First Split Hand, H11
            shoe->dealToPlayer(player, handIndex);

            //If Player Decides to Split H11, and doesn't have a pair of Aces
            if(player->makeDecision(player->getHand(handIndex)) == player->SPLIT && !((player->getHand(handIndex))->isPairAces())) {
                
                //Split there first Hand, H11 again      < H11, H12 >  ->   < H111, H112, H12 >       
                player->split(handIndex);
                splits++;
            }

            if(splits > 1) {
                eval(player, handIndex);   //Eval H111
                handIndex++;
                eval(player, handIndex);   //Eval H112
                handIndex++;
            } else {
                eval(player, handIndex);   //Eval H11
                handIndex++;
            }
            

            //Evaluate Second/Third Split Hand, H12
            shoe->dealToPlayer(player, handIndex);

            //If Player Decides to Split H12, and doesn't have a pair of Aces
            if(player->makeDecision(player->getHand(handIndex)) == player->SPLIT && !((player->getHand(handIndex))->isPairAces())) {
                
                //Split there Second Hand, H12 again      < H111, H112, H12 >  ->   < H111, H112, H121, H122 >
                player->split(handIndex);
                splits++;
            }

            if(splits > 2) {
                eval(player, handIndex);   //Eval H121
                handIndex++;
                eval(player, handIndex);   //Eval H122
            } else {
                eval(player, handIndex);   //Eval H12
            }

        } else {

            //If No Split, Proceed Normally by Evaluating Initial & Only Hand
            eval(player, handIndex);

        }
    }


    //Deal the Dealer Until Bust, BlackJack or Stand
    Hand* dealerHand = dealer->getHand();
    dealerHand->printHand();
    while(!(dealerHand->isBust()) && !(dealerHand->isBlackJack()) && !(dealer->makeDecision() == dealer->STAND)) {
        shoe->dealToDealer(dealer);
        dealerHand->printHand();
    }

    if(dealerHand->isBust()) {
        cout << "Dealer Busts!" << endl;                           
    }

    if(dealerHand->isBlackJack()) {  
        cout << "Dealer has BlackJack!" << endl;                                          
    }
}

void Table::collectionsAndPayOuts() {
    for(auto& pair : players) {         //For Each Player
        Player* player = pair.second;
        Hand* dealerHand = dealer->getHand();
        bool playerSplit;
        
        //If More than 1 Hand, Player Has Split this Round
        if(player->getHands().size() > 1) {
            playerSplit = true;
        } else {
            playerSplit = false;
        }

        for(auto& playerHand : player->getHands()) {  //For Each Hand Player Has
            //DETERMINE BET MULTIPLIER DEPENDING ON REGULAR OR HIT OR SURRENDER
            int betFactor = 1;  

            if(playerHand->getBetType() == Hand::SURRENDER) {       //Halve Money
                betFactor = 0.5;
            } else if(playerHand->getBetType() == Hand::DOUBLE) {   //Double Money
                betFactor = 2;
            }

            //IF PLAYER SURRENDERED HAND
            if(playerHand->getBetType() == Hand::SURRENDER) {
                player->decreaseBalance(betFactor * player->getBet());

            // Player busts or has less points than dealer (who didn't bust) = LOSE
            } else if(playerHand->isBust() || (playerHand->getHandValue() < dealerHand->getHandValue() && !dealerHand->isBust())) {
                player->decreaseBalance(betFactor * player->getBet());
                cout << "Player " << player->getTablePos() << " Loses! New Balance = " << player->getBalance() << endl; 

            // Player has more points than dealer OR Player has Less Points than Dealer AND Dealer Busted
            } else if((playerHand->getHandValue() > dealerHand->getHandValue()) || !playerHand->isBust() && dealerHand->isBust()) {

                // Player has a blackjack & Player hasn't Split & Player Hasn't Doubled
                if(playerHand->isBlackJack() && !playerSplit && betFactor != 2) {
                    player->increaseBalance(1.5 * player->getBet());        //Return 1.5x   (When Player splits or doubles, blackjack does not return 1.5, only 1x & 2x respectively)

                // Player wins but doesn't have a blackjack
                } else {
                    player->increaseBalance(betFactor * player->getBet());        
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
    (dealer->getHand())->clearHand();
    for(auto& pair : players) {                         //For Each Player
        (pair.second)->clearAllHands();               //Clear All their Hands
    }
}