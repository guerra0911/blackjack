#include "player.h"
#include "hand.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <numeric>
#include <math.h>
#include <iomanip>  //Floating Point Precision

using namespace std;
using std::string;
using std::vector;
using std::map;
using std::unordered_map;
using std::ofstream;
using std::fixed;
using std::setprecision;

#define NUM_DECKS 8
#define PRINT true


//Constructors
Player::Player(float initialBalance, float initialBet, Strategy initialStrategy, int cycles) {
    balance = initialBalance;
    bet = initialBet;
    strategy = initialStrategy;

    //Reserve Space in data and initialize it as empty
    data.resize(cycles);
    //Initialize Empty Initial Hand
    hands.push_back(new Hand());

    reinitializeCardCount();
}

Player::~Player() {
    for (Hand* hand : hands) {
        delete hand;
    }
}


//Balance
float Player::getBalance() {
    return balance;
}

void Player::setBalance(float newBal) {
    balance = newBal;
}

void Player::increaseBalance(float amount) {
    balance += amount;
}

void Player::decreaseBalance(float amount) {
    balance -= amount;
}


//Bet
float Player::getBet() {
    return bet;
}

void Player::placeBet(float amount) {
    bet = amount;
}


//Hand
Hand* Player::getHand(int handIndex) {
    return hands[handIndex];
}

vector<Hand*> Player::getHands() {
    return hands;
}

void Player::clearAllHands() {
    for(auto& hand : hands) {
        hand->clearHand();          //Empty The Hand
        delete hand;                //Delete It
    }
    hands.clear();

    //Add a new REGULAR Empty Hand object to the vector so it is not empty for future operations/accessing
    hands.push_back(new Hand());
}

void Player::split(int handIndex) {
    Hand* splitHand = new Hand();
    hands.insert(hands.begin() + handIndex + 1, splitHand);

    (getHand(handIndex + 1))->addCardToHand((getHand(handIndex))->getCard(1));      //Move 2nd card in first hand to 1st card in 2nd split hand     <1,2> -> <1,2> , <2,_>
    (getHand(handIndex))->removeCardFromHand(1);                                    //Remove 2nd card in first hand      <1,2> , <2,_> -> <1,_> , <2,_>

    if(PRINT) {
        for(Hand* hand : getHands()) {
            hand->printHand();
        }
    }

}


//Decision
Player::Decision Player::makeDecision(Hand* hand, int dealerCardVal) {
    switch(strategy) {

        case HARD_17:
            if(hand->getHandValue() >= 17) {
                return Player::Decision::S;
            } else {
                return Player::Decision::H;
            }
            break;

        case SOFT_17:
            if(hand->getHandValue() > 17) {
                return Player::Decision::S;
            } else if(hand->getHandValue() == 17 && !hand->hasAce()) {
                return Player::Decision::S;
            } else {
                return Player::Decision::H;
            }
            break;
        
        case OPTIMAL_CHART:
            return opChart(hand, dealerCardVal);
            break;
    }   
}


//Table
int Player::getTablePos() {
    return tablePos;
}

void Player::setTablePos(int position) {
    tablePos = position;
}


//Optimal Chart
vector<vector<Player::Decision>> Player::optimalChart = {

    //Player                      Dealer's Card
    // Hand       A    2    3    4    5    6    7    8    9    10

    //If Hand has More than 2 Cards OR (Has 2 Cards AND No Ace AND No Double)
    /* 8 */     { H,   H,   H,   H,   H,   H,   H,   H,   H,   H  },
    /* 9 */     { H,   H,   DH,  DH,  DH,  DH,  H,   H,   H,   H  },
    /* 10 */    { H,   DH,  DH,  DH,  DH,  DH,  DH,  DH,  DH,  H  },
    /* 11 */    { DH,  DH,  DH,  DH,  DH,  DH,  DH,  DH,  DH,  DH },
    /* 12 */    { H,   H,   H,   S,   S,   S,   H,   H,   H,   H  },
    /* 13 */    { H,   S,   S,   S,   S,   S,   H,   H,   H,   H  },
    /* 14 */    { H,   S,   S,   S,   S,   S,   H,   H,   H,   H  },
    /* 15 */    { H,   S,   S,   S,   S,   S,   H,   H,   H,   RH },
    /* 16 */    { RH,  S,   S,   S,   S,   S,   H,   H,   RH,  RH },
    /* 17 */    { S,   S,   S,   S,   S,   S,   S,   S,   S,   S  },

    //If Player has an Ace, and it is not double Aces (Only 2 Cards in Hand)
    /* A,2 */   { H,   H,   H,   H,   DH,  DH,  H,   H,   H,   H  },
    /* A,3 */   { H,   H,   H,   H,   DH,  DH,  H,   H,   H,   H  },
    /* A,4 */   { H,   H,   H,   DH,  DH,  DH,  H,   H,   H,   H  },
    /* A,5 */   { H,   H,   H,   DH,  DH,  DH,  H,   H,   H,   H  },
    /* A,6 */   { H,   H,   DH,  DH,  DH,  DH,  H,   H,   H,   H  },
    /* A,7 */   { H,   DS,  DS,  DS,  DS,  DS,  S,   S,   H,   H  },
    /* A,8 */   { S,   S,   S,   S,   S,   S,   S,   S,   S,   S  },
    /* A,9 */   { S,   S,   S,   S,   S,   S,   S,   S,   S,   S  },
    /* A,10 */  { S,   S,   S,   S,   S,   S,   S,   S,   S,   S  },

    //If Player has Double Cards (Only 2 Cards in Hand)
    /* A,A */   { P,   P,   P,   P,   P,   P,   P,   P,   P,   P  },
    /* 2,2 */   { H,   P,   P,   P,   P,   P,   P,   H,   H,   H  },
    /* 3,3 */   { H,   P,   P,   P,   P,   P,   P,   H,   H,   H  },
    /* 4,4 */   { H,   H,   H,   H,   P,   P,   H,   H,   H,   H  },
    /* 5,5 */   { H,   DH,  DH,  DH,  DH,  DH,  DH,  DH,  DH,  H  },
    /* 6,6 */   { H,   P,   P,   P,   P,   P,   H,   H,   H,   H  },
    /* 7,7 */   { H,   P,   P,   P,   P,   P,   P,   H,   H,   H  },
    /* 8,8 */   { P,   P,   P,   P,   P,   P,   P,   P,   P,   P  },
    /* 9,9 */   { S,   P,   P,   P,   P,   P,   S,   P,   P,   S  },
    /* 10,10 */ { S,   S,   S,   S,   S,   S,   S,   S,   S,   S  },
};

Player::Decision Player::opChart(Hand* playerHand, int dealerCardVal) {
    //If Player over 17 without an Ace, STAND
    if(playerHand->getHandValue() >= 17 && !playerHand->hasAce()) {
        return Player::S;
    }

    //If Player Under 8, HIT
    if(playerHand->getHandValue() < 8) {
        return Player::H;
    }

    //If Hand has More than 2 Cards OR (Has 2 Cards AND No Ace AND No Double)
    if(playerHand->getSize() > 2 || !playerHand->hasAce() && !playerHand->isDoubles()) {
        return optimalChart[playerHand->getHandValue() - 8][dealerCardVal - 1];               //-8: Chart Starts at Card Value 8
    }

    //If Player has an Ace, and it is not double Aces (Only 2 Cards in Hand)
    else if(playerHand->hasAce() && !playerHand->isDoubles()) {
        return optimalChart[playerHand->cardNotAce() + 8][dealerCardVal - 1];
    }

    //If Player has Double Cards (Only 2 Cards in Hand)
    else if(playerHand->isDoubles()) {
        int doubledCardVal = (playerHand->getCard(0))->getFaceValue();
        return optimalChart[doubledCardVal + 18][dealerCardVal - 1];
    }

    cout << "NO DECISION RETURNED FROM CHART -> ERROR" << endl;

}

//Data
void Player::addData(int round) {
    data[round].push_back( getBalance() );
}

void Player::averageData() {

    int numCycles = data.size();
    int maxLength = 0;
    for (const auto& vector : data) {
        maxLength = max(maxLength, static_cast<int>(vector.size()));    //Cycle with the Most Turns
    }

    vector<float> averages(maxLength, 0.0);  
    vector<float> counts(maxLength, 0.0);

    for (const auto& vector : data) {                               //For Each Cycle (Vector/Row in Data)
        for (int turn = 0; turn < vector.size(); ++turn) {          //For Each Turn
            averages[turn] += vector[turn];                         //Add the balance at respective turn to Averages Vector
            counts[turn]++;                                         //Keep Track of how # of times, this turn is reached
        }
    }

    for (int i = 0; i < averages.size(); ++i) {             //For each turn index in Averages
        averages[i] /= numCycles;                           //Divide Sum of balances by numCycles to get average
        counts[i] /= numCycles * 100.0;                     //% of Cycles that Reached this Turn                 
    }

    data.clear();                               //Clear the Data (If add vector<float> averages to Player, then this is OPTIONAL)
    data.push_back(averages);                   //Push back the averages
    data.push_back(counts);
    
}


void Player::printData() {
    int totalRounds = data.size();
    cout << "[ ";
    for(int round = 0; round < totalRounds; round++) {
        int totalTurns = data[round].size();
        cout << "[";
        for(int turn = 0; turn < totalTurns; turn++) {
            cout << fixed << setprecision(2) << data[round][turn];  //Print only 2 Decimal Places
            if(turn != totalTurns - 1) {
                cout << ", ";
            }
        }
        cout << "]";
        if(round != totalRounds - 1) {
            cout << ", " << endl;
        }
    }
    cout << "]" << endl << endl;
}

void Player::writeDataToCSV(const string& filename) {
    ofstream file("Plotting/" + filename);

    int totalRounds = data.size();

    // Determine the maximum number of turns
    int maxTurns = 0;
    for (const auto& round : data) {
        if (round.size() > maxTurns) {
            maxTurns = round.size();
        }
    }

    for(int round = 0; round < totalRounds; round++) {
        for(int turn = 0; turn < maxTurns; turn++) {
            if (turn < data[round].size()) {
                //This round has this turn, write the balance
                file << fixed << setprecision(2) << data[round][turn];  //Write Only 2 Decimal Places
            } else {
                //This round does not have this turn, write a placeholder value
                file << "NaN";
            }
            if(turn != maxTurns - 1) {
                file << ", ";
            }
        }
        file << "\n";
    }
}

//Card Counting
int Player::getCardCount(Card::Rank rank) {
    return cardCount[rank];
}

void Player::reinitializeCardCount() {
    //Initialize cardCount
    for(int c = Card::Rank::ACE; c <= Card::Rank::KING; c++) {
        cardCount[static_cast<Card::Rank>(c)] = NUM_DECKS*4;                 //Count # of Each Rank in Shoe
    }
}

void Player::decCardCount(Card* card) {
    Card::Rank decRank = (card->getRank());         //Get Rank of Card that was just Burnt
    cardCount[static_cast<Card::Rank>(decRank)]--;  //Decrement its balance in the Shoe
}

void Player::printCardCount() {
    for (const auto& pair : cardCount) {
        //pair.first = Rank, pair.second = Frequency
        cout << Card::rankStringMap[pair.first] << ": " << pair.second << endl;
    }
    cout << endl;
}

float Player::probGet(int desiredHandVal) {
    
}

float Player::probNotBust() {
    
}

float Player::probBlackJack() {

}


