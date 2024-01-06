#include "table.h"
#include "hand.h"
#include "card.h"
#include <iostream>

#define PRINT false

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
    //delete players[position];       //Delete the Player from existence
    players.erase(position);        //Erase them from the map
}

Player* Table::playerAtPos(int position) {
    return players[position];
}

//Shoe
void Table::reinitializeShoe() {
    shoe->reinitialize();
    shoe->shuffle();
    shoe->burnCard();

    //cout << "Shoe Reinitialized" << endl;

    for(auto& pair : players) {
        (pair.second)->reinitializeCardCount();
    }
}

int Table::cardsLeftAtTable() {
    return shoe->cardsLeft();
}


//Play
void Table::dealToPlayer(Player* player, int handIndex) {
    Card* dealtCard = shoe->dealCard();
    (player->getHand(handIndex))->addCardToHand(dealtCard);

    for(auto& pair : players) {                     //For Each Player at Table
        (pair.second)->decCardCount(dealtCard);     //Dec Card Count for All Players
    }
}

void Table::dealToDealer() {
    Card* dealtCard = shoe->dealCard();
    (dealer->getHand())->addCardToHand(dealtCard);

    if( (dealer->getHand())->getSize() >= 2) {          //If Not hidden card
        for(auto& pair : players) {                     //For Each Player at Table
            (pair.second)->decCardCount(dealtCard);     //Dec Card Count for that Visible Card
        }
    }    
}

void Table::revealHiddenDealerCard() {
    for(auto& pair : players) {                                         //For Each Player at Table
        (pair.second)->decCardCount((dealer->getHand())->getCard(0));   //Dec Card Count for Hidden Card
    }
}

void Table::playRound() {
    //Deal 1st Card to Each Player
    for(auto& pair : players) {
        dealToPlayer(pair.second,0);      //Index 0 = First Initial Hand
    }

    //Deal 1st Card (HIDDEN) to Dealer
    dealToDealer();

    //Deal 2nd Card to Each Player
    for(auto& pair : players) {
        dealToPlayer(pair.second,0);      //Index 0 = First Initial Hand
        if(PRINT) {(pair.second->getHand(0))->printHand();}
        if(PRINT) {
            pair.second->printCardCount();  
            pair.second->probGet(20, pair.second->getHand(0));
            pair.second->probNotBust(pair.second->getHand(0));
            pair.second->probBlackJack(pair.second->getHand(0));
        }    
    }

    //Deal 2nd Card (VISIBLE) to Dealer
    dealToDealer();
    Card* dealerCard = (dealer->getVisibleCard());
    int dealerCardVal = dealerCard->getFaceValue();
    if(PRINT) {dealer->printVisibleCard();}



    //For Each Player, Deal Until Bust, BlackJack or Stand
    for(auto& pair : players) {
        int handIndex = 0;
        int splits = 0;

        Player* player = pair.second;  
        Hand* playerHand = player->getHand(handIndex);
        Player::Decision decision = player->makeDecision(playerHand, dealerCardVal);
       

        //If Player Decided to Split
        if(decision == player->P) {
            
            //Split there First Hand    < H1 >  ->  < H11, H12>
            if(PRINT) cout << "Splits Hand " << splits + 1 << " time" << endl;
            
            player->split(handIndex);
            splits++;

            //Deal Second Card to First Split Hand, H11
            dealToPlayer(player, handIndex);
            if(PRINT) playerHand->printHand();
            decision = player->makeDecision(playerHand, dealerCardVal);     //Re-Evaluate Newly Split Hand

            //If Player Decides to Split H11, and doesn't have a pair of Aces
            if(decision == player->P && !(playerHand->isPairAces())) {
                
                //Split there first Hand, H11 again      < H11, H12 >  ->   < H111, H112, H12 >  
                if(PRINT) cout << "Splits Hand " << splits + 1 << " times" << endl;
                player->split(handIndex);
                splits++;
            }

            if(splits > 1) {
                playerHand = player->getHand(handIndex);    //Use H111
                dealToPlayer(player, handIndex);  //Deal Second Card to H111
                if(PRINT) playerHand->printHand();
                eval(player, handIndex, dealerCardVal);   //Eval H111
                handIndex++;

                playerHand = player->getHand(handIndex);    //Use H112
                dealToPlayer(player, handIndex);  //Deal Second Card to H112
                if(PRINT) playerHand->printHand();
                eval(player, handIndex, dealerCardVal);   //Eval H112
                handIndex++;
            } else {
                eval(player, handIndex, dealerCardVal);   //Eval H11
                handIndex++;
            }
            

            //Deal Second Card to Second/Third Split Hand, H12
            playerHand = player->getHand(handIndex);    //Use H12
            dealToPlayer(player, handIndex);
            if(PRINT) playerHand->printHand();
            decision = player->makeDecision(playerHand, dealerCardVal);     //Re-Evaluate Newly Split Hand

            //If Player Decides to Split H12, and doesn't have a pair of Aces
            if(decision == player->P && !(playerHand->isPairAces())) {
                
                //Split there Second Hand, H12 again      < H111, H112, H12 >  ->   < H111, H112, H121, H122 >
                if(PRINT) cout << "Splits Hand " << splits + 1 << "times" << endl;
                player->split(handIndex);
                splits++;
            }

            if(splits > 2) {
                playerHand = player->getHand(handIndex);    //Use H121
                dealToPlayer(player, handIndex); //Deal Second Card to H121
                if(PRINT) playerHand->printHand();
                eval(player, handIndex, dealerCardVal);   //Eval H121
                handIndex++;


                playerHand = player->getHand(handIndex);    //Use H122
                dealToPlayer(player, handIndex); //Deal Second Card to H122
                if(PRINT) playerHand->printHand();
                eval(player, handIndex, dealerCardVal);   //Eval H122
            } else {
                eval(player, handIndex, dealerCardVal);   //Eval H12
            }


        } else {
            //If No Split, Proceed Normally by Evaluating Initial & Only Hand
            eval(player, handIndex, dealerCardVal);

        }
    }


    //Deal the Dealer Until Bust, BlackJack or Stand
    Hand* dealerHand = dealer->getHand();
    if(PRINT) {dealerHand->printHand();}
    revealHiddenDealerCard();               //Reveal Card so Players can modify card Count

    while(!(dealerHand->isBust()) && !(dealerHand->isBlackJack()) && !(dealer->makeDecision() == dealer->S)) {
        dealToDealer();
        if(PRINT) {dealerHand->printHand();}
    }

    if(dealerHand->isBust()) {
        if(PRINT) cout << "Dealer Busts!" << endl;                         
    }

    if(dealerHand->isBlackJack()) {  
        if(PRINT) cout << "Dealer has BlackJack!" << endl;                                         
    }
}

void Table::eval(Player* player, int handIndex, int dealerCardVal) {
    Hand* playerHand = player->getHand(handIndex);
    Player::Decision decision;

    //While Player hasnt Busted, Hasn't Hit BlackJack, Hasn't Decided to Stand, Hasn't gone over 21, keep asking to play
    while(!playerHand->isBust() && !playerHand->isBlackJack() && playerHand->getHandValue() < 22) {
        decision = player->makeDecision(playerHand, dealerCardVal);

        //SURRENDER
        if(decision == player->RH) {
            if(playerHand->getSize() < 3) {                         //If Doubling is Allowed then Double(Only After 2 Initial Cards Dealt)
                if(PRINT) cout << "PLAYER SURRENDERED" << endl;
                playerHand->setBetType(Hand::HALF);                 //Indicate 0.5x Payout
                break;                                              //Only allowed one more card after doubling so break
            } 
            
            else {  //If Surrender is not Allowed, bc it is not the first turn, then hit
                if(PRINT) cout << "SURRENDER NOT ALLOWED SO HIT" << endl;
                dealToPlayer(player, handIndex);
                if(PRINT) playerHand->printHand();
                playerHand->setBetType(Hand::REGULAR);
            }
            //cout << "NO SURRENDER DECISION MADE -> ERROR" << endl;
        }

        //If Split, then Just Hit, b/c if you are in this eval function, you are not allowed to split anymore
        else if (decision == player->P) {
            if(PRINT) cout << "SPLIT NOT ALLOWED SO HIT" << endl;
            dealToPlayer(player, handIndex);
            if(PRINT) playerHand->printHand();
            playerHand->setBetType(Hand::REGULAR);
        }

        //STAND
        else if (decision == player->S) {
            if(PRINT) cout << "STAND" << endl;
            playerHand->setBetType(Hand::REGULAR);
            break;
        }

        //DOUBLE
        else if(decision == player->DS || decision == player->DH) {
            
            if(playerHand->getSize() < 3) {                 //If Doubling is Allowed then Double(Only After 2 Initial Cards Dealt)
                if(PRINT) cout << "PLAYER DOUBLED" << endl;
                playerHand->setBetType(Hand::DOUBLE);       //Indicate 2x Payout
                dealToPlayer(player, handIndex);
                if(PRINT) playerHand->printHand();
                break;                                      //Only allowed one more card after doubling so break
            }
            
            else if (decision == player->DS) {              //If double is not allowed, then otherwise stamd
                if(PRINT) cout << "DOUBLE NOT ALLOWED SO STAND" << endl;
                playerHand->setBetType(Hand::REGULAR);
                break;                                      //Stand
            } 
            
            else {                                          //If double is not allowed, then otherwise hit
                if(PRINT) cout << "DOUBLE NOT ALLOWED SO HIT" << endl;
                dealToPlayer(player, handIndex);
                if(PRINT) playerHand->printHand();
                playerHand->setBetType(Hand::REGULAR);
            }
            //cout << "NO DOUBLE DECISION MADE -> ERROR" << endl;
        }
        
        //HIT
        else if(decision == player->H) {
            if(PRINT) cout << "HIT" << endl;
            dealToPlayer(player, handIndex);
            if(PRINT) playerHand->printHand();
            playerHand->setBetType(Hand::REGULAR);
        }
        
    }

    if(playerHand->isBust()) {
        if(PRINT) cout << "Player " << player->getTablePos() << " Busts!" << endl;                           
    }

    if(playerHand->isBlackJack()) {  
        if(PRINT) cout << "Player " << player->getTablePos() << " has BlackJack!" << endl;                                          
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
            float betFactor = 1.0;  

            if(playerHand->getBetType() == Hand::HALF) {       ////IF PLAYER SURRENDERED HAND Halve Money
                betFactor = 0.5;
                player->decreaseBalance(betFactor * (float)player->getBet());
                if(PRINT) cout << "Return Halved, Player" << player->getTablePos() << " Surrenders! Loses " << betFactor * player->getBet() <<  ", New Balance = " << player->getBalance() << endl;
                continue;
            } else if(playerHand->getBetType() == Hand::DOUBLE) {   //Double Money
                if(PRINT) cout << "Return Doubled!" << endl;
                betFactor = 2.0;
            }

            // Player busts or has less points than dealer (who didn't bust) = LOSE
            if(playerHand->isBust() || ((playerHand->getHandValue() < dealerHand->getHandValue()) && !dealerHand->isBust())) {
                player->decreaseBalance(betFactor * player->getBet());
                if(PRINT) cout << "Player " << player->getTablePos() << " Loses! New Balance = " << player->getBalance() << endl; 

            // Player has more points than dealer OR Player has Less Points than Dealer AND Dealer Busted
            } else if((playerHand->getHandValue() > dealerHand->getHandValue()) || !playerHand->isBust() && dealerHand->isBust()) {

                // Player has a blackjack & Player hasn't Split & Player Hasn't Doubled
                if(playerHand->isBlackJack() && !playerSplit && betFactor != 2) {
                    player->increaseBalance(1.5 * player->getBet());        //Return 1.5x   (When Player splits or doubles, blackjack does not return 1.5, only 1x & 2x respectively)

                // Player wins but doesn't have a blackjack
                } else {
                    player->increaseBalance(betFactor * player->getBet());        
                }
                if(PRINT) cout << "Player " << player->getTablePos() << " Wins! New Balance = " << player->getBalance() << endl;

            // Player and dealer have the same points
            } else {
                if(PRINT) cout << "Player " << player->getTablePos() << " Draws." << endl;
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

void Table::addAllData(int round) {
    for(auto& pair : players) {
        (pair.second)->addData(round);
    }
}