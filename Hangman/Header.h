#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <random>

using namespace std;

class Hangman {

private:
	string word;
	vector<string> words;
	void startGame();
	vector<string> createWordList();
	string guesses;
	int maxGuesses;
	string message;
	bool verifyGuess(string guess);
	void checkForWin();
	int currentGuessCount;

public:
	Hangman();
	void displayWord();
	void displayMessage();
	void makeGuess();
	int getMaxGuesses();
	int getGuessCount();
	void lostGame();
};
