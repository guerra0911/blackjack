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


//To String & Int
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

int Card::rankToInt(Card::Rank rank) {
    static map<Card::Rank, int> rankIntMap = {
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

    return rankIntMap[rank];
}
