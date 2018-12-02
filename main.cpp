// hangman.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <random>

using namespace std;

bool checkVal(char c, string word, string& guess)
{
	bool found = false;
	for (int i = 0; i < word.length(); i++)
	{
		if (word[i] == c)
		{
			guess[i] = c;
			found = true;
		}
	}
	return found;

}

void printGuess(char guess[])
{
	for (int i = 0; i <= 0; i++)
	{
		cout << guess[i];
	}

}


long getRandNum()
{
	random_device rd;     // only used once to initialise (seed) engine
	mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	uniform_int_distribution<int> uni(0, 966); // guaranteed unbiased

	auto random_integer = uni(rng);
	return random_integer;
}

string getWordFromList()
{

	ifstream inFile;
	inFile.open("words.txt");
	string line;
	long times = getRandNum();

	//check for error
	if (inFile.fail())
	{
		cout << "error";
	}
	

	for (int i = 0; i < times; i++)
	{
		inFile >> line;
	}

	return line;

}


string getWord()
{

	cout << "Enter word/phrase: ";
	string word;
	getline(cin, word);
	system("cls");
	return word;
	
}



void displayMan(int penalty)
{
	if (penalty == 0)
	{
		cout << "\n      ___" << endl
			<< "     |   |" << endl
			<< "         |" << endl
			<< "         |" << endl
			<< "         |" << endl
			<< "         |" << endl
			<< "       -----" << endl;
	}
	else if (penalty == 1)
	{
		cout << "\n      ___" << endl
			<< "     |   |" << endl
			<< "     O   |" << endl
			<< "         |" << endl
			<< "         |" << endl
			<< "         |" << endl
			<< "       -----" << endl;
	}
	else if (penalty == 2)
	{
		cout << "\n      ___" << endl
			<< "     |   |" << endl
			<< "     O   |" << endl
			<< "     |   |" << endl
			<< "         |" << endl
			<< "         |" << endl
			<< "       -----" << endl;
	}
	else if (penalty == 3)
	{
		cout << "\n      ___" << endl
			<< "     |   |" << endl
			<< "     O   |" << endl
			<< "   --|   |" << endl
			<< "         |" << endl
			<< "         |" << endl
			<< "       -----" << endl;
	}
	else if (penalty == 4)
	{
		cout << "\n      ___" << endl
			<< "     |   |" << endl
			<< "     O   |" << endl
			<< "   --|-- |" << endl
			<< "         |" << endl
			<< "         |" << endl
			<< "       -----" << endl;
	}
	else if (penalty == 5)
	{
		cout << "\n      ___" << endl
			<< "     |   |" << endl
			<< "     O   |" << endl
			<< "   --|-- |" << endl
			<< "    /    |" << endl
			<< "         |" << endl
			<< "       -----" << endl;
	}
	else if (penalty == 6)
	{
		cout << "\n      ___" << endl
			<< "     |   |" << endl
			<< "     O   |" << endl
			<< "   --|-- |" << endl
			<< "    / \\  |" << endl
			<< "         |" << endl
			<< "       -----" << endl;
	}
}

void remLetters(char letters[], char c)
{
	cout << "\nLetter choices: ";
	for (int i = 0; i < 26; i++)
	{
		if (c == letters[i])
		{
			letters[i] = NULL;
		}
		cout << letters[i] << " ";
	}
	cout << "\n\n";
}


int main()
{

	string word;
	cout << "Let's play Hangman!\n";
	displayMan(6);
	
	char playAgain = 'y';
	while (playAgain = 'y')
	{
		string guess = "";
		int penalty = 0;
		char letters[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
		
		cout << "Choose 1 for random word or 0 for supplied word/phrase:\n";
		int choice;
		cin >> choice;
		
		system("cls"); //clear
		
		if (choice == 0)
		{
			word = getWord();
		}
		else
		{
			word = getWordFromList();
		}

		//initialize guess array with '_'s
		for (int i = 0; i < word.length(); i++)
		{
			if (word[i] == ' ')
			{
				guess += ' ';
			}
			else
			{
				guess += '_';
			}
		}

		cout << "The word/phrase is " << word.length() << " letters long\n";
		cout << guess << "\n" << endl;
		int rounds = 0;
		
		//prompts for guesses while word is not guessed and penalties are less than 7
		while (word.compare(guess) != 0 && penalty < 6)
		{
		
			char c;

			cout << "Enter guess (or type # to guess the word/phrase): ";
			cin >> c;
			if (rounds > 0)
			{
				system("cls"); //clear
			}
			if (c == '#')
			{
				cin.get();
				cout << "Enter guess: ";
				string wordGuess;
				getline(cin, wordGuess);

				if (word.compare(wordGuess) == 0)
				{
					break;
				}
				else
				{
					penalty++;
					cout << "Wrong! Guess again! (or type # to guess the word/phrase)\n";
					
				}
			}
			else if (checkVal(c, word, guess))
			{
				cout << "\nWord: " << guess << endl;
			}
			else
			{
				penalty++;
				cout << "Wrong! Guess again! (or type # to guess the word/phrase)\n";
				
				cout << "\nWord: " << guess << endl;
			}
			displayMan(penalty);
			remLetters(letters, c);
			rounds++;

		}
		if (penalty < 6)
		{
			cout << "Congratulations! You won!\n";
		}
		else
		{
			cout << "Sorry, you lost. The word was: " << word << endl;
		}

		cout << "\n\n Play again? (y or n): ";
		cin >> playAgain;
		cout << "\n\n";
	}

	
	return 0;
}


