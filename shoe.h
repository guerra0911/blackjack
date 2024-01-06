#ifndef SHOE_H
#define SHOE_H

#include "card.h"
#include "player.h"
#include "dealer.h"
#include <vector>
#include <map>

using std::vector;
using std::map;

class Shoe {
    public:

    //Constructors
    Shoe(int numDeck);          //Initializes a shoe with # of decks
    ~Shoe();

    //Getters
    Card* getTopCard();         //Get FaceCard
    int getSize();
    
    //Actions
    void shuffle();             //Shuffles current cards in Shoe
    void reinitialize();        //Adds all cards back to shoe, reshuffles
    int cardsLeft();            //Checks How many Cards Left in Shoe
    void burnCard();            //Burns Top Card

    //Print
    void printShoe();

    //Dealing
    void dealToPlayer(Player* player, int handIndex);    //Deal Card to Player's Specified Hand & Remove from Shoe
    void dealToDealer(Dealer* dealer);


    private:
    int position;                       //Current Position in Deck to Deal
    int numDecks;                       //Number of decks to make shoe with
    vector<Card*> shoe;                 //All cards in shoe
    
};

#endif //SHOE_H