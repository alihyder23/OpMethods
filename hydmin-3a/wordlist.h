#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include"d_except.h"

using namespace std;

class wordlist
{
public:
	wordlist();						// default constructor
	wordlist(const string &dfln);		// constructor
	bool wordLookup(string word) const;	// finds a word in the dictionary
	void printWordList();					// prints the dictionary
private:
	void readWordList(string fln);
	vector<string> wordVect;
};


/* dictionary default constructor */
wordlist::wordlist()
{
	readWordList("wordlist");
} // constructor

/* dictionary constructor */
wordlist::wordlist(const string &fln)
{
	readWordList(fln);
} // constructor

/* reads all words in the dictionary and puts them into a vector */
void wordlist::readWordList(string dfln)
{
	string word;
	ifstream fin;
	fin.open(dfln.c_str());
	if (! fin)
	{
		throw fileOpenError(dfln);
	}
	cout << "Loading Wordlist...";

	////
	while (getline(fin, word))
	{
		wordVect.push_back(word);
	}
	////

	fin.close();
	cout << '\r' << "Wordlist loaded.   " << endl;
} // readDict

/* find words in the dictionary */
bool wordlist::wordLookup(string w) const
{
	for (int i = 0; i < wordVect.size(); i++)
	{
		if (wordVect[i] == w)
		{
			return true;
		}
	} // for

	return false;
} // wordLookup

/* print all words in the dictionary (sanity check, not recommended) */
void wordlist::printWordList()
{
	for (int i = 0; i < wordVect.size(); i++)
	{
		cout << wordVect[i] << endl;
	}
} // printDict