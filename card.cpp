#include "card.h"
#include <map>
#include <string>

using std::map;
using std::string;
using std::map;

//Constructors
Card::Card(Card::Rank rank, Card::Suit suit) : rank(rank), suit(suit) {

    
}

Card::~Card() { }


//Getters
Card::Rank Card::getRank() {
    return rank;
}

Card::Suit Card::getSuit() {
    return suit;
}

int Card::getFaceValue() {
    int faceValue = static_cast<int>(rank);     //Number that Enum equals
    if(faceValue > 10) {                        //J = 11, Q = 12, K = 13 in Enum Definition
        faceValue = 10;                         //Set them back equal to 10
    }
    return faceValue;
}


//To String & Int
string Card::toString() {
    string cardString = rankStringMap[rank] + " of " + suitStringMap[suit];
    return cardString;

}

int Card::rankToInt(Card::Rank rank) {
    return rankIntMap[rank];
}

string Card::rankToString(Card::Rank rank) {
    return rankStringMap[rank];
}


//Static Maps
map<Card::Rank, string> Card::rankStringMap = {
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

map<Card::Rank, int> Card::rankIntMap = {
    {ACE, 1},
    {TWO, 2},
    {THREE, 3},
    {FOUR, 4},
    {FIVE, 5},
    {SIX, 6},
    {SEVEN, 7},
    {EIGHT, 8},
    {NINE, 9},
    {TEN, 10},
    {JACK, 10},
    {QUEEN, 10},
    {KING, 10}
};

map<Card::Suit, string> Card::suitStringMap = {
    {SPADES, "SPADES"},
    {HEARTS, "HEARTS"},
    {DIAMONDS, "DIAMONDS"},
    {CLUBS, "CLUBS"}
};