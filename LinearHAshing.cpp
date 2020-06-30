// LinearHAshing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstring>
#include <vector>
#include <math.h>
#include <iomanip>
#include <fstream>
#include<stdio.h>
#include <stdlib.h>
#include <string>
#include<iostream>

using namespace std;

int power(int a, int b)
{
	for (int i = 0; i<b; i++)
	{
		a *= a;
	}
	return a;
};

struct Bucket
{
string  word;
};

const int size = 100;

class LProbing
{
private:
	int a; //a constant which is used in hashing
	int cursize;  //current size of hash table
	Bucket *Table;  //pointer to array of struct
	int loadfactor; //ratio of number of elements entered over size of hashtable
	int n;  //number of elements entered
	Bucket table[size];   //array of structs
public:
	LProbing(int A);  //constant is decided by user 
	void resize();
	void insert(string word);
	void Lookup(string word);
};

LProbing::LProbing(int A)
{
	cursize = size;
	a = A;
	Table = table;
	loadfactor = 0;  //initially loadfactor is 0 as number of elements entered are 0
	n = 0;
}

void LProbing::resize()
{
	//cout << "resize" << endl;
	printf("\nresize");
	loadfactor = n / cursize;   //ensuring if resize needs to be done
	if (loadfactor <= 0.7)
	{
		return;
	}
	const int s = 2 * cursize;
	Bucket PTable[100];//change
	for (int i = 0; i<cursize; i++)
	{
		if (Table[i].word.empty())
			continue;

		//rehashing the word onto the new array
		string w = Table[i].word;
		int key = 0;
		for (int j = 0; j<w.size(); j++)
		{
			unsigned char b = (unsigned char)w[j];
			key += (int)power(a, i)*b;
		}
		key = key % (2 * cursize);
		PTable[key].word = w;  //entering the word in the new array
	}
	Table = PTable;  //putting pointer equal to new array
	cursize = 2 * cursize;  //doubling the current size of array
}

void LProbing::insert(string word)
{
	//cout << "1" << endl;
	printf("\nIteration : %d",n);
	n++;  //incrementing the number of elements entered with every call to insert

	//if loadfactor is greater than 0.5, resize array
	loadfactor = n / cursize;
	if (loadfactor>0.5)
	{
		resize();
	}
	//hashing the word
	int k = 0;
	for (int i = 0; i<word.size(); i++)
	{
		unsigned char b = (unsigned char)word[i];
		int c = (int)((power(a, i))*b);
		k += c;
		//cout << c << endl;
		printf("\nHash Value: %d",c);
	}

	int key = 0;
	key = k%cursize;
	//cout << key << endl;
	printf("\nKey: %d", key);
	//if the respective key index is empty enter the word in that slot
	if (Table[key].word.empty() == 1)
	{
		//cout << "initial empty slot" << endl;
		printf("\n\ninitial empty slot");
		Table[key].word = word;
	}
	else  //otherwise enter in the next slot
	{
		//searching array for empty slot
		while (Table[key].word.empty() == 0)
		{
			k++;
			key = k%cursize;
		}
		//when empty slot found,entering the word in that bucket
		Table[key].word = word;
		//cout << "word entered" << endl;
		printf("\nword entered");
	}
}

//#include "Linear Probing.cpp"
//#include <fstream>
//
//using namespace std;


int main()
{
	char a;
	LProbing H(35);
	ifstream fin;
	fin.open("dict.txt");
	vector<string> D;

	string d;
	while (getline(fin, d))
	{
		if (!d.empty())
		{
			D.push_back(d);
		}
	}
	fin.close();
	for (int i = 0; i<D.size(); i++)
	{
		printf("\nInserting Element %S:", D[i]);
		cout << D[i];
		H.insert(D[i]);
	}

	//system("PAUSE");

	a = getchar();

	return 0;
}

