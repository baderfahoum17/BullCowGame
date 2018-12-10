#pragma once
#include<string>
using int32 = int;
using FString = std::string;


// two variables inisalised to 0
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};
class FBullCowGame
{
public:
	FBullCowGame(); //constractur 


	int32 GetMaxTries() const;
	int32 GetCurrentTries() const;
	int32 GetHiddenWordLenght() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;// TODO make a more rich return value 
	

	void Reset(); // TODO make a more rich reset method 

	// counts bulls and cows, and increases try# assuming valued guess
	FBullCowCount SubmitValidGuess(FString);


private:
	//see constractur  
	int32 myCurrentTries;
	FString MyHiddenWord;
	bool bGameIsWon=false;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};

