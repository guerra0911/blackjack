#include "card.h"
#include "player.h"
#include "dealer.h"
#include <vector>

using std::vector;

class Shoe {
    public:

    //Constructors
    Shoe(int numDeck);          //Initializes a shoe with # of decks
    ~Shoe();

    //Getters
    Card* getFaceCard();         //Get FaceCard
    
    //Actions
    void shuffle();             //Shuffles current cards in Shoe
    void reinitialize();        //Adds all cards back to shoe, reshuffles

    //Dealing
    void dealToPlayer(Player* player);    //Deal Card to Player & Remove from Shoe
    void dealToDealer(Dealer* dealer);


    private:
    vector<Card*> shoe;         //All cards in shoe
    int position;               //Current Position in Deck to Deal
    int numDecks;               //Number of decks to make shoe with
};