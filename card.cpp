#include "card.h"

//Constructors
Card::Card(Card::Rank rank, Card::Suit suit) : rank(rank), suit(suit) {}

Card::~Card() { }

//Getters
Card::Rank Card::getRank() {
    return rank;
}

Card::Suit Card::getSuit() {
    return suit;
}

int Card::getFaceValue() {
    return static_cast<int>(rank); 
}