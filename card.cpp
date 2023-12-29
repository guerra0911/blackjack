#include "card.h"

Card::Card(Card::Rank rank, Card::Suit suit) : rank(rank), suit(suit) {}

Card::~Card() { }

Card::Rank Card::getRank() {
    return rank;
}

Card::Suit Card::getSuit() {
    return suit;
}

int Card::getFaceValue() {
    return static_cast<int>(rank); 
}