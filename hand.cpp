#include "hand.h"
#include "card.h"
#include <iostream>
#include <string>

using namespace std;

//Constructors
Hand::Hand() {
    betType = BetType::REGULAR;
}

Hand::~Hand() {
    for(auto& card : hand) {
        delete card;
    }   
}


//Hand
void Hand::addCardToHand(Card* card) {
    hand.push_back(card);
}

void Hand::removeCardFromHand(int cardIndex) {
    if (cardIndex < hand.size() && cardIndex >= 0) {
        hand.erase(hand.begin() + cardIndex);
    }
    else {
        cout << "Card Index is Out of Range, Card cannot be Removed" << endl;
    }
}

void Hand::clearHand() {
    hand.clear();               //Do not delete cards as they need to exist in shoe
}

int Hand::getHandValue() {
    int handValue = 0;
    bool hasAce = false;        //Initially Assume No Ace

    for(Card* card : hand) {
        if(card->getRank() == card->ACE) {
            hasAce = true;
        }
        handValue += card->getFaceValue();
    }

    //If Ace is Present, and Counting Ace as 11 will not cause bust, count as 11 by adding 10 to intial 1 added above
    //If there is more than 1 ace, only one can be considered as 11 without causing bust, so this works for any # of aces
    if(hasAce && handValue <= 11) {
        handValue += 10;
    }

    return handValue;
}

Card* Hand::getCard(int cardIndex) {
    return hand[cardIndex];
}


//Status
void Hand::setBetType(Hand::BetType newBetType) {
    betType = newBetType;
}

Hand::BetType Hand::getBetType() {
    return betType;
}


//Actions
bool Hand::isBust() {
    if(getHandValue() > 21) {
        return true;
    } 
    return false;
}

bool Hand::isBlackJack() {
    if(getHandValue() == 21) {
        return true;
    } 
    return false;
}

bool Hand::isPairAces() {
    if(hand.size() > 2) {
        cout << "HAND TOO LARGE TO CHECK FOR PAIR ACES" << endl;
    }

    if((getCard(0))->getRank() == Card::ACE && (getCard(1))->getRank() == Card::ACE) {
        return true;
    } else {
        return false;
    }
}

bool Hand::isDoubles() {

    if(hand.size() > 2) {
        cout << "HAND TOO LARGE TO CHECK FOR DOUBLES" << endl;
    }

    if((getCard(0))->getRank() == (getCard(1))->getRank()) {
        return true;
    } else {
        return false;
    }
}

bool Hand::hasAce() {
    for(Card* card : hand) {
        if(card->getRank() == Card::ACE) {
            return true;
        }
    }
    return false;
}

int Hand::getSize() {
    return hand.size();
}

int Hand::cardNotAce() {
    for(Card* card : hand) {
        if(card->getRank() != Card::ACE){
            return card->getFaceValue();
        }
    }
}

//Print
void Hand::printHand() {
    for(size_t i = 0; i < hand.size(); ++i) {
        if(hand[i] == nullptr) {
            cout << "CARD IS NULL POINTER ERROR!!!!!!!!!!!!!!!!!!" << endl;
        }
        cout << hand[i]->toString();
        if(i != hand.size() - 1) {      // If it's not the last card
            cout << ", ";
        }
    }
    cout << " = " << getHandValue() << endl;
}