#include "card.h"
#include <map>
#include <string>

using std::map;
using std::string;

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


//To String
string Card::toString() {
    static map<Card::Rank, string> rankMap = {
        {ACE, "ACE"},
        {TWO, "TWO"},
        {THREE, "THREE"},
        {FOUR, "FOUR"},
        {FIVE, "FIVE"},
        {SIX, "SIX"},
        {SEVEN, "SEVEN"},
        {EIGHT, "EIGHT"},
        {NINE, "NINE"},
        {TEN, "TEN"},
        {JACK, "JACK"},
        {QUEEN, "QUEEN"},
        {KING, "KING"}
    };

    static map<Card::Suit, string> suitMap = {
        {SPADES, "SPADES"},
        {HEARTS, "HEARTS"},
        {DIAMONDS, "DIAMONDS"},
        {CLUBS, "CLUBS"}
    };

    string cardString = rankMap[rank] + " of " + suitMap[suit];

    return cardString;

}