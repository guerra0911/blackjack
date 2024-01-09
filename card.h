#ifndef CARD_H
#define CARD_H

#include <string>
#include <map>
using std::string;
using std::map;

class Card {
    public:

    enum Rank {
        ACE = 1,
        TWO = 2,
        THREE = 3,
        FOUR = 4,
        FIVE = 5,
        SIX = 6,
        SEVEN = 7,
        EIGHT = 8,
        NINE = 9,
        TEN = 10,
        JACK = 11,
        QUEEN = 12,
        KING = 13
    };

    enum Suit {
        SPADES,
        HEARTS,
        DIAMONDS,
        CLUBS
    };

    //Constructors
    Card(Rank rank, Suit suit);    
    ~Card();                        

    //Getters
    Card::Rank getRank();           //Rank Getter
    Card::Suit getSuit();           //Rank Setter
    int getFaceValue();             //Rank to Int Value

    //To String & Int
    string toString();
    int rankToInt(Card::Rank rank);
    string rankToString(Card::Rank rank);

    //Static Maps
    static map<Card::Rank, string> rankStringMap;
    static map<Card::Rank, int> rankIntMap;
    static map<Card::Suit, string> suitStringMap;

    private:
    Rank rank;
    Suit suit;
};

#endif //CARD_H 