#include "shoe.h"

#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>


Shoe::Shoe(int numDecks) : numDecks(numDecks) {
    shoe.reserve(52*numDecks);

    for (int s = Card::Suit::SPADES; s <= Card::Suit::CLUBS; s++) {     //For each Suit
        for(int r = Card::Rank::ACE; r <= Card::Rank::KING; r++) {      //For Each Rank

            Card::Suit newSuit = static_cast<Card::Suit>(s);            //Convert Integer s to type Suit based on enumeration association
            Card::Rank newRank = static_cast<Card::Rank>(r);            //Convert Integer r to type Rank based on enumeration association
            
            Card newCard(newRank, newSuit);                             //Create a New Card with the new rank & suit in iteration
            shoe.push_back( newCard );                                  //Add that new card to the shoe
        
            //shoe.push_back(Card(static_cast<Card::Rank>(r), static_cast<Card::Suit>(s)));
        }
    }
}

Card Shoe::getFaceCard() {
    return shoe.front();
}

void Shoe::dealCardToPlayer(/*player*/) {
    //playerHand.push_back(shoe.front());       //Adds Card to Player Hand
    //shoe.erase(shoe.begin());                 //Removes it from the shoe
}

void Shoe::shuffle() {
    std::random_device rd;                      //Random Device Object
    std::mt19937 g(rd());                       //Mersenne Twister Random Generator
    std::shuffle(shoe.begin(), shoe.end(), g);  //Shuffle Vector Algorithm
}

void Shoe::reinitializeShoe() {
    shoe.insert(shoe.end(), garbage.begin(), garbage.end());    //Concatenate shoe & garbage
    garbage.clear();                                            //Restart Garbage
    shuffle();                                                  //Shuffle newly concatenated shoe
}

Shoe::~Shoe() {}
