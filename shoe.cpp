#include "shoe.h"

#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>

//Constructors
Shoe::Shoe(int numDecks) : numDecks(numDecks), position(0) {
    shoe.reserve(52*numDecks);

    for(int deck = 0; deck < numDecks; deck++) {                            //Repeat numDeck amount of times
        for (int s = Card::Suit::SPADES; s <= Card::Suit::CLUBS; s++) {     //For each Suit
            for(int r = Card::Rank::ACE; r <= Card::Rank::KING; r++) {      //For Each Rank

                Card::Suit newSuit = static_cast<Card::Suit>(s);            //Convert Integer s to type Suit based on enumeration association
                Card::Rank newRank = static_cast<Card::Rank>(r);            //Convert Integer r to type Rank based on enumeration association
                
                Card* newCard = new Card(newRank, newSuit);                 //Create a Pointer to a New Card with the new rank & suit in iteration
                shoe.push_back( newCard );                                  //Add that new card object itself to the shoe
            
            }
        }
    }
}

Shoe::~Shoe() {
    for (Card* card : shoe) {   //For each card in the shoe
        delete card;            //Delete each card
    }
}


//Getters
Card* Shoe::getFaceCard() {
    return shoe[position];                      //Return card at current dealing position
}


//Actions
void Shoe::shuffle() {
    std::random_device rd;                      //Random Device Object
    std::mt19937 g(rd());                       //Mersenne Twister Random Generator
    std::shuffle(shoe.begin(), shoe.end(), g);  //Shuffle Vector Algorithm
}

void Shoe::reinitialize() {
    position = 0;
    shuffle();
}

//Dealing
void Shoe::dealToPlayer(Player* player) {
    player->addCardToHand( getFaceCard() );
    position++;
}

void Shoe::dealToDealer(Dealer* dealer) {
    dealer->addCardToHand( getFaceCard() );
    position++;
}

