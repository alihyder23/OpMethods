//Ali Hyder
//Luke Mino-Altherr
//Project 2a
//Microsoft Visual Studio

#include "stdafx.h"
#include "deck.h"

using namespace std;

int main()
{
        try
        {
                deck dk;

                // prints a deck of cards
                cout << dk;
        }
        catch (rangeError &re)
        {
                cout << re.what() << endl;
        }

		system("pause");
		return(0);
}