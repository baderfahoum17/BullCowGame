/* this  is the console executable, that makes use of the BullCow class
this acts as the view in a MVC pattern, and is responsible for all user intraction.
for game logiv see the FBullCowGame class*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"
using FText = std::string;
using int32 = int;
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //initialization of a game
FBullCowGame player2game;

// the entry point of our application 
int main()
{	
	std::cout << BCGame.GetCurrentTries();

	bool flag = false;
	do {
		PrintIntro();
		PlayGame();
		flag = AskToPlayAgain();
	} while (flag);
	//exit the game
	return 0;
	
}

// introduce the game
void PrintIntro() {
	std::cout << ") Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLenght();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "NICELY DONE! you won!. \n" << "took you " << BCGame.GetCurrentTries()-1 << " attempts!" ;
	}
	else {
		std::cout << "better luck next time!";
	}
}

void PlayGame() {
	BCGame.Reset();
	int32 maxTries = BCGame.GetMaxTries();
	std::cout << "max num of tires: " << maxTries << "\n";

	//loop for the number of turns asking for guesses untill we run out or game is won 
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTries() <= maxTries) {
		FText guess = "";
		guess = GetValidGuess(); //TODO make loop checking valid 

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(guess);
		//print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls << std::endl;
		std::cout << "Cows = " << BullCowCount.Cows << std::endl;
	
		// repeat the guess back to them
	//	std::cout << " Your guess was: " << guess;
	//	std::cout << std::endl;

		
	}
	PrintGameSummary();

}
// loop untill you get a valid guess from the player
FText GetValidGuess() { 
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		int32 tries = BCGame.GetCurrentTries();
		//get a guess from the player
		std::cout << "Enter guess number " << tries << " out of " << BCGame.GetMaxTries() << ": ";
		
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);


		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << " please enter a word without repeating letters \n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << " please enter only a lowercase letters\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << " please enter a " << BCGame.GetHiddenWordLenght() << " letter word.\n";
			break;
		default: // we assume the guess is valid
			tries++;
		}
	} while (Status != EGuessStatus::OK); // KEEP LOOPING UNTIL WE GET A VALID INPUT
	return Guess;

}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again y/n? ";
	FText	Response = "";
	std::getline(std::cin, Response);
	std::cout << "first char of your answer is " << Response[0];

	return ((Response[0] == 'y') || (Response[0] == 'Y'));
	
}
