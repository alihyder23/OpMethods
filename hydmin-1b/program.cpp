//Ali Hyder
//Luke Mino-Altherr
//Project 1b
//dev C++

#include "hydmin-1b.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
        try
        {
                // initialize the length and range variables
                int n, m;

                // prompt the user to enter integers for the code length and digit range
                cout << "Enter code length (n) and digit range (m)" << endl;
                cout << "n: ";
                cin >> n;
                cout << "m: ";
                cin >> m;
        
                // initialize a code object using the input length and range
                mastermind mstr(n, m);

                // output the secret code and prompt user for the number of guesses to play
                mstr.startGame();

                // play the game for the specified number of guesses
                mstr.playGame();
        }
        catch (rangeError &re)
        {
                cout << re.what() << endl;
                system("pause");
                exit(0);
        }
        system("pause");
}
