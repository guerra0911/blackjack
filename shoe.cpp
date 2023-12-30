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
Card* Shoe::getTopCard() {
    return shoe[position];                      //Return card at current dealing position
}


//Actions
void Shoe::shuffle() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();    //Use current time as a seed for the random generator
    std::mt19937 g(seed);                                                       //Mersenne Twister Random Generator
    std::shuffle(shoe.begin(), shoe.end(), g);                                  //Shuffle Vector Algorithm
}

void Shoe::reinitialize() {
    position = 0;
}

int Shoe::cardsLeft() {
    return numDecks*52 - position;
}

void Shoe::burnCard() {
    position++;
}

//Dealing
void Shoe::dealToPlayer(Player* player) {
    player->addCardToHand( getTopCard() );
    position++;
}

void Shoe::dealToDealer(Dealer* dealer) {
    dealer->addCardToHand( getTopCard() );
    position++;
}

