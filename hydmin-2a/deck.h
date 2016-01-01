

#include "card.h"
#include "d_node.h"

using namespace std;

/* deck class */
class deck
{
public:
        deck();                // default constructor
        friend ostream &operator<<(ostream &ostr, const deck &d);
private:
        node<card> *front;
};

/* default constructor for deck 
   creates a deck of cards [2 - Ace] and [Clubs - Spades]
*/
deck::deck()
{
        node<card> *curr = NULL;

        /* loops through each suit starting at Spades since we want spades to 
           be the last suit when we go through and print out the deck
        */
        for (int i = 3; i >= 0; i--)
        {
                /* loops through each card value [2 - Ace]
                */
                for (int val = 14; val > 1; val--)
                {
                        /* creates a new node that contains a single card consisting
                           of a card value and a card suit
                        */
                        front = new node<card> (card(val, i), curr);
                        
                        curr = front;
                } // end for
        } // end for
}


/* Overload the '<<' operator for deck objects */
ostream &operator<<(ostream &ostr, const deck &d)
{
        node<card> *card = d.front;

        // while the card doesn't point to NULL, we print the list 
        while (card != NULL)
        {
                ostr << card->nodeValue << endl;
                card = card->next;
        }

        return ostr;
}