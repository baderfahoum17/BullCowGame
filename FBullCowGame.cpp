#include "FBullCowGame.h"
#include <map>
#define TMap std::map


using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}


int FBullCowGame::GetCurrentTries() const
{	return myCurrentTries;	}
int32 FBullCowGame::GetHiddenWordLenght() const 
{	return MyHiddenWord.length();	}

bool FBullCowGame::IsGameWon() const
{	
	return bGameIsWon;	
}

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet"; // must be an isogram 
	MyHiddenWord = HIDDEN_WORD;

	myCurrentTries = 1;
	bGameIsWon = false;
	return;
}
// receives a VALID GUESS, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString word)
{	
	FString GuessedWord = word;
	myCurrentTries++;
	// setup a return variable
	FBullCowCount BullCowCount;

	int32 HiddenWordLength = GetHiddenWordLenght();
	// loop through all the letters in the guess
	for (int32 i = 0; i < HiddenWordLength; i++) {
		// compare letters against the hidden word
		for (int32 j = 0; j < HiddenWordLength; j++) {
			// if they match then 
			if (GuessedWord[i] == MyHiddenWord[j]) {
				// increment bulls if theyre in the same place
				if (i == j) {
					BullCowCount.Bulls++;
				}
				// increment cows if not 
				else {
					BullCowCount.Cows++;
				}
			}
		}	
	}
	if (BullCowCount.Bulls == HiddenWordLength) {
		bGameIsWon = true;
	}
	else { 
		bGameIsWon = false;  
	}
	return BullCowCount;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
// if the guess isn't a n isogram
	if(!IsIsogram(guess)) { 
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(guess)) { // TODO write function
		return EGuessStatus::Not_Lowercase;
	}
	else if (guess.length() != GetHiddenWordLenght() ) {
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}

}

bool FBullCowGame::IsIsogram(FString word) const {
	if (word.length() <= 1) { return true; }
	TMap<char, bool> LetterSeen;
	for (auto Letter : word) // for all letters of the word
	{
		Letter = tolower(Letter); //handle case sensitivity 
		if (LetterSeen[Letter]) { // if letter in the map
			return false; // not an Isogram
		}else {
			LetterSeen[Letter] = true; // add letter to the map as seen 
		}

	}
	return true;
}

bool FBullCowGame::IsLowercase(FString word) const {
		for (auto Letter : word) {
			if (!islower(Letter)) {
				return false;
			}
		}
		return true;
}