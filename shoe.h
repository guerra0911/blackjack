#include "card.h"
#include <vector>

using std::vector;

class Shoe {
    public:

    Shoe(int numDeck);          //Initializes a shoe with # of decks

    ~Shoe();

    Card getFaceCard();         //Get facecard to be dealt
    
    void dealCardToPlayer();

    void shuffle();             //Shuffles current cards in Shoe

    void reinitializeShoe();    //Adds all discarded cards back and shuffles shoe

    private:
    vector<Card> shoe;
    vector<Card> garbage;
    int numDecks;
};