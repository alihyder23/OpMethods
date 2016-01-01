#include "d_random.h"
#include "d_except.h"
#include <iostream>
#include <vector>

using namespace std;

class code
{
public:
        // Constructor:
        code(int length, int range);
        // code operations:
        vector<int> guess();
        int checkCorrect(const vector<int> &guess);
        int checkIncorrect(const vector<int> &guess);
        int getN() { return n; }
        int getM() { return m; }
        friend ostream &operator<<(ostream &ostr, const code &c);
private:
        int n, m;                                // size of length and range
        vector<int> randCode;        // Random Code vector
        vector<int> inputVect;        // Input Code vector
}; // end class

/* Constructor
*/
code::code(int length, int range)
        : n(length), m(range)
{
        // check inputs
        if (n < 0)
    {
        throw rangeError("Cannot generate code with a negative length.");
    }
    if (m < 0)
    {
        throw rangeError("Cannot generate code with a negative range.");
    }


        // generate a random number vector 'n' digits long with a range of 'm'
        randomNumber rand;
        
        for (int i = 0; i < n; i++)
        {
                randCode.push_back(rand.random(m));
        } // end for
}

/* Prompt user for a guess, push each guess into a vector
*/
vector<int> code::guess()
{
        int i, num;
        inputVect.clear();

        cout << "\nEnter a " << n << " digit guess." << endl;

        for (i = 0; i < n; i++)
        {
                cout << "Digit " << i+1 << ": ";
                cin >> num;
                
                if(num<0||num>m)
                {
                    throw rangeError("Guess is outside range.");
                }

                inputVect.push_back(num);
        } // end for

        if (inputVect.size() != randCode.size())
        {
                throw rangeError("Vectors are not the same size.");
        }

        return inputVect;

} // end guess

/* Compare each value of the vectors with each other
   Output the number of correct digit in correct location 
*/
int code::checkCorrect(const vector<int> &guess)
{
        // check inputs
        if (guess.size() < n)
    {
        throw rangeError("ERROR: Was expecting a vector of length n");
    }


        // check for correct digits
        int correct = 0;

        for(int i = 0; i < guess.size(); i++)
        {
                if (guess[i] == randCode[i])
                {
                        correct += 1;
                } // end if
        } // end for

        return correct;

} // end checkCorrect

/* Compare each value of the vectors with each other
   Output the number of correct digits in the incorrect location
*/
int code::checkIncorrect(const vector<int> &guess)
{
        vector<int> temp = guess;
        int incorrect=0;
        
        for(int i=0; i<n; i++)
        {
                if (randCode[i]==temp[i])
                {
                    temp[i]=-1;
                }
                else
                {
                 for (int j=0; j<n;j++)
                {
                    if(randCode[i]==temp[j])
                    {
                         temp[j]=-1;
                         incorrect++;  
                         break;
                    }
                }
                }
        }  
        return(incorrect);
} // end checkIncorrect


/* Overload the '<<' operator for a vector of type 'T'
*/
template <typename T>
ostream &operator<<(ostream &ostr, const vector<T> &v1)
{
        ostr << "< ";

        for (int i = 0; i < v1.size(); i++)
        {
                ostr << v1[i] << " ";
        } // end for

        ostr << ">";

        return ostr;
}

/* Overload the '<<' operator for code objects
*/
ostream &operator<<(ostream &ostr, const code &c)
{
        ostr << c.randCode;
        return ostr;
}
