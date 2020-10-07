// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    PrintLine(TEXT("The hidden word is: %s"), *HiddenWord); // Debug line

    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else  // Checking player's guess
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    // Welcoming the player
    PrintLine(TEXT("Welcome to the Bull Cow Game!"));

    HiddenWord = TEXT("cake");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Please guess the %i-letter word\nYou have %i lives\nPress 'Enter' to continue..."), HiddenWord.Len(), Lives);
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again..."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    // Correct guess
    if (HiddenWord == Guess) 
    {
        PrintLine(TEXT("GG you win! "));
        EndGame();
        return;
    }

    // Wrong length for guess
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Your guess is the wrong number of characters\nThe hidden word is %i-letters long"), HiddenWord.Len());
        return;
    } 

    // Guess has repeating letters (i.e. not an isogram)
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("Your guess has repeating letters, try again!"));
        return;
    }

    PrintLine(TEXT("You have lost a life\nYou have %i lives remaining"), Lives);

    if (--Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left...\nThe hidden word was: %s\nGAME OVER"), *HiddenWord);
        EndGame();
        return; 
    }
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    for (int32 i = 0; i < Word.Len(); i++)
    {
        for (int32 j = i+1; j < Word.Len(); j++)
        {
            if (Word[i] == Word[j])
            {
                return false;
            }
        }
    }
    
    return true;
}