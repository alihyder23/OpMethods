//Ali Hyder
//Luke Mino-Altherr
//Project 3b
//Microsoft Visual Studio
//Number of string comparison = 15210742
#include "stdafx.h"
#include <iostream>
#include <time.h>
#include "grid.h"
#include "wordlist.h"

using namespace std;

int wordCount = 0;

/* adjacentCheck function
   adjacentCheck checks for words around a letter in all directions
*/
void adjacentCheck(const wordlist &d,		// wordlist object
				   const grid &g,			// grid object
				   int row,					// row index
				   int col,					// column index
				   const int dX,			// change in x-direction
				   const int dY,			// change in y-direction
				   const int minWL = 5)		// minimum word length
{
	// make sure we will actually move from starting point
	if (dX == 0 && dY == 0) { return; }

	// set grid index
	int x = row;
	int y = col;
	string currWord = g[x][y];

	// find words that are longer than the minimum size
	while (currWord.length() <= g.getSize())
	{
		if (currWord.length() >= minWL)
		{
			// use binarySearch to check if word is in the wordlist
			if (d.binarySearch(0, d.getSize()-1, currWord))
			{
					cout << currWord << endl;
					wordCount++;
			} // if
		} // if

		// handle wrap-around cases
		x = (x + dX + g.getSize()) % g.getSize();
		y = (y + dY + g.getSize()) % g.getSize();
		currWord = currWord + g[x][y];
	} // while
} // adjacentCheck

/* findMatches function
   finds any words in the grid that match the wordlist
*/
void findMatches(const wordlist &wlist, const grid &grd)
{
	time_t start, end;
	double diff;

	cout << "Searching...\n" << endl;
	time (&start);

	for (int j = 0; j < grd.getSize(); j++)
	{
		for (int i = 0; i < grd.getSize(); i++)
		{
			// check N
			adjacentCheck(wlist, grd, j, i, -1, 0);
			// check NE
			adjacentCheck(wlist, grd, j, i, -1, 1);
			// check E
			adjacentCheck(wlist, grd, j, i, 0, 1);
			// check SE
			adjacentCheck(wlist, grd, j, i, 1, 1);
			// check S
			adjacentCheck(wlist, grd, j, i, 1, 0);
			// check SW
			adjacentCheck(wlist, grd, j, i, 1, -1);
			// check W
			adjacentCheck(wlist, grd, j, i, 0, -1);
			// check NW
			adjacentCheck(wlist, grd, j, i, -1, -1);
		} // for
	} // for

	cout << '\n' << wordCount << " words found." << endl;
	cout<<"Number of words compared: "<< compare_count <<endl;
	time (&end);
	diff = difftime(end, start);
	printf("Runtime: %.2f minutes.\n", diff/60);
} // findMatches

/* testSearch function
   gets a wordlist and grid and finds matches
*/
void testSearch()
{

	// get wordlist filename
	/*
	string wordFN;
	cout << "Input the wordlist filename: ";
	cin >> wordFN;
	wordlist word(dictFN);
	*/
	wordlist wlist("wordlist");
	wlist.sort();

	// get grid filename
	string gridFN;
	cout << "Input the grid filename: ";
	cin >> gridFN;
	grid grd(gridFN);

	// find all matching words in the grid
	findMatches(wlist, grd);
} // testSearch

int main()
{
	try
	{
		// search the given grid for given words
		testSearch();
		system("pause");
	}
	catch (fileOpenError &foe)
	{
		cout << foe.what() << endl;
	}
	catch (indexRangeError &ire)
	{
		cout << ire.what() << endl;
	}
} // main