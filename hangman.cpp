
#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>


using namespace std;


int getWord()
{
	vector<string> words;
	ifstream file("wordlist.txt");
	string line;
	while (getline(file, line)) words.push_back(line);

	cout << words[rand() % words.size()] << endl;

	return 0;
}