#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "d_except.h"

int compare_count = 0;

using namespace std;

class wordlist
{
public:
	wordlist();						// default constructor
	wordlist(const string &dfln);		// constructor
	void printwordList();					// prints the wordlist
	void sort();						// sorts the dictionary based on the algorithm
	bool binarySearch(int first, int last, string target) const;
	int getSize() const { return numLines; } 
private:
	void readwordList(string fln);	
	vector<string> wordVect;
	int numLines;
};


/* wordlist default constructor */
wordlist::wordlist()
{
	readwordList("wordlist");
} // constructor

/* wordlist constructor */
wordlist::wordlist(const string &fln)
{
	readwordList(fln);
} // constructor

/* reads all words in the wordlist and puts them into a vector */
void wordlist::readwordList(string dfln)
{
	ifstream fin;

	fin.open(dfln.c_str());
	if (! fin)
	{
		throw fileOpenError(dfln);
	}
	cout << "Loading Wordlist...";

	// initialize
	string word;
	string tmp;
	numLines = 0;
	int wordIndex = 0;

	// count the number of lines in the wordlist
	while (getline(fin, tmp)) { numLines++; } 

	fin.clear();							// clear
	fin.seekg(0, ios::beg);					// return to beginning of file
	wordVect = vector<string>(numLines);	// preallocate vector for speed

	while (getline(fin, word))				// place words from the wordlist
	{										// file into a vector
		wordVect[wordIndex++] = word;		// much faster than push_back
	}

	fin.close();
	cout << '\r' << "Wordlist loaded.   " << endl;
	system("pause");
} // readwordList

/* binarySearch function */
bool wordlist::binarySearch(int first, int last, string target) const
{
	
	if (first > last) 
	{ 
		return false; 
	} // if
	else if (first == last) 
	{ 
		return target.compare(wordVect[first]) == 0; 
		compare_count++;
	} // else if

    while (first < last)
	{
		int mid = (first + last) / 2;
		int compare = target.compare(wordVect[mid]);
		compare_count++;

		if (compare == 0)
		{
			return true;
		} // if
		else if (compare < 0)
		{
			// recurse
			return binarySearch(first, mid, target);
		} // else if
		else
		{
			// recurse
			return binarySearch(mid + 1, last, target);
		} // else
	} // while
} // binarySearch

/* partition function */
int partition(vector<string> &words, int first, int last, int pivot)
{
	string p = words[first];
	int i = first;
	int j = last+1;
	do
	{
		do
		{i++;}
		while
		(words[i] < p && i < last);

		do
		{j--;}
		while(words[j] > p);

		swap(words[i], words[j]);
	}
	while(i<j);
	swap(words[i], words[j]);
	swap(words[first], words[j]);
	return j;
} // partition

/* selection sort function */
void selectsort(vector<string> &words)
{
	string temp;
	int min;

	for (int i = 0; i < words.size() - 1; i++)
	{
		min = i;

		for ( int j = i + 1; j < words.size() - 1; j++)
		{
			if (words[j] < words[min])
			{
				min = j;
			} // if
		} // for

		temp = words[i];
		words[i] = words[min];
		words[min] = temp;
	} // for
} // selectsort

/* quicksort function */
void quicksort(vector<string> &words, int first, int last)
{
	if (first < last)
	{
		int p = (first + last) / 2;
		p = partition(words, first, last, p);
		quicksort(words, first, p - 1);
		quicksort(words, p + 1, last);
	} // if
} // quicksort

/* sort function */
void wordlist::sort()
{
	//selectsort(wordVect); //)(n^3logk + k^2)
	quicksort(wordVect, 0, wordVect.size()-1);//O(n^3logk + klogk)
} // sort

/* print all words in the wordlist (sanity check, not recommended) */
void wordlist::printwordList()
{
	for (int i = 0; i < wordVect.size(); i++)
	{
		cout << wordVect[i] << endl;
	}
} // printWordList