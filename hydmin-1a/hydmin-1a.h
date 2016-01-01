#include <iostream>
#include <vector>
#include <ctime>
#include "d_random.h"

using namespace std;

class BadInput{};

class Code
{
public:
        Code(int length = 5, int range = 5);
		void setCode();
        void printCode() const;
        void guess();
        int checkCorrect() const;
private:
        int m, n;                    // length and range
        vector<int> randCode;        // Random Code vector
        vector<int> userCode;       // User Code vector
}; // end class

Code::Code(int length, int range)
        :n(length), m(range)
{
    randomNumber rnd;
 	for (int i = 0; i < n; i++)
    {
                randCode.push_back(rnd.random( time(0)) % m); //Generates a random number from 1 to m
    }       
}

void Code::setCode()
{
    randomNumber rnd;
	cout<<"Enter the number of digits in the code: ";
	cin>> n;
	
	cout<<endl;
	cout<<"Enter the range of number in the code: ";
	cin>> this->m;

   Code(n,m);
}

void Code::printCode() const//prints secret code
{

        for (int i = 0; i < n; i++)
        {
                cout << randCode[i];
        }
}

int Code::checkCorrect() const//Output how many numbers the user guessed correctly in the correct spot.
{
        int count = 0;

        for(int i = 0; i < n; i++)
        {
                if (randCode[i] == userCode[i])
                {
                        count += 1;
                } 
        } 

        return(count);
}

void Code::guess()  // Prompt user for a guess, push each guess into a vector
{
        int num, p;
        userCode.clear();
		
		p=(m+n)/2;

		cout << "You get "<<p<<" chances to guess "<<n<<" numbers from 0-"<<m<<endl;

		for (int i=1; i<p+1 ;i++)
		{
            userCode.clear();   
            int correct; 
            
			cout << "Enter guess number "<<i<<endl;
			cout << "Enter a number one at a time."<<endl;

			for (int i = 1; i < n+1; i++)
			{
                bool checkinput=true; 
                 while(checkinput) 
                 {    
                  cout << i << ": ";
                  cin >> num;
                  try
                  {
                      if(num>m||num<0)
                      {
                          
                          throw BadInput();
                      }
                      else
                      {
                          checkinput=false;
                      }
                  }
                
                catch (BadInput)
                {
                      cout<<"Number is not in range between 0-"<<m<<endl;
                      cout<<"Guess a new number"<<endl;
                      
                }
                }
                      userCode.push_back(num);
                } 
			correct=this->checkCorrect();
			if(correct==n)
			{
                 cout<<"You got them all correct!"<<endl;
                 break;
            }
            else
            {
                cout<<"You guessed "<<correct<<" numbers correctly"<<endl;
		}
}
}
