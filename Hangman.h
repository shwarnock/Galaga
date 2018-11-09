#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <random>

using namespace std;

class Hangman {

private:
	//methods
	void startGame();
	vector<string> createWordList();
	bool verifyGuess(string guess);
	void checkForWin();

	//variables
	string word;
	vector<string> words;
	string guesses;
	int maxGuesses;
	string message;

	int currentGuessCount;

public:
	//methods
	Hangman();
	void displayWord();
	void displayMessage();
	void makeGuess();
	int getMaxGuesses();
	int getGuessCount();
	void lostGame();
};
