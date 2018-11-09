#include "Hangman.h"

Hangman::Hangman() {
	startGame();
}

vector<string> Hangman::createWordList() {
	vector<string> words;
	string word;
	ifstream file;
	file.open("C:/Users/Shawn/source/repos/Hangman/Hangman/Words.txt");
	while (getline(file, word)) {
		words.push_back(word);
	}
	file.close();
	return words;
}

void Hangman::startGame() {
	words = createWordList();

	//Get a random number
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<> distr(0, words.size() - 1);
	int index = distr(eng);

	word = words[index];
	transform(word.begin(), word.end(), word.begin(), toupper);
	message = "Please make a guess: ";
	maxGuesses = 7;
	currentGuessCount = 0;
}

void Hangman::displayWord() {
	string display;
	for (char c : word) {
		if (guesses.find(c) != string::npos) {
			display = display + c + " ";
		}
		else {
			display = display + "_ ";
		}
	}
	cout << display << endl << endl;
}

void Hangman::displayMessage() {
	cout << message << endl << endl;
}

void Hangman::makeGuess() {
	string guess;
	cin >> guess;
	transform(guess.begin(), guess.end(), guess.begin(), toupper);
	if (verifyGuess(guess)) {
		guesses = guesses + guess;
		checkForWin();
	}
}

void Hangman::checkForWin() {
	for (char c : word) {
		if (guesses.find(c) == string::npos) {
			return;
		}
	}

	cout << "You Win!!";
	exit(1);
}

bool Hangman::verifyGuess(string guess) {

	if (guess.length() != 1 || regex_match(guess, regex("[^a-zA-Z]"))) {
		cout << "That is an invalid guess. Guess should be one letter character" << endl;
		return false;
	}
	else if (guesses.find(guess) != string::npos) {
		cout << "That letter has alread been guessed. Try again." << endl;
		return false;
	} 
	++currentGuessCount;
	return true;
}

int Hangman::getGuessCount() {
	return currentGuessCount;
}

int Hangman::getMaxGuesses() {
	return maxGuesses;
}

void Hangman::lostGame() {
	cout << "You lose";
}