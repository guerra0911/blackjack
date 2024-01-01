#ifndef CARD_H
#define CARD_H

#include <string>
using std::string;

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
        JACK = 10,
        QUEEN = 10,
        KING = 10
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

    private:
    Rank rank;
    Suit suit;
};

#endif //CARD_H