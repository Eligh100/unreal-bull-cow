// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Loading in the hidden words
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArrayWithPredicate(Isograms, *WordListPath, [](const FString& CurrentWord)
    {
       return CurrentWord.Len() >= 4 && CurrentWord.Len() <= 8 && IsIsogram(CurrentWord.ToLower());
    }); 

    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else  // Checking player's guess
    {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame()
{
    // Welcoming the player
    PrintLine(TEXT("Welcome to the Bull Cow Game!"));

    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num()-1)];
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Please guess the %i-letter word\nYou have %i lives\nPress 'Enter' to continue..."), HiddenWord.Len(), Lives);
    PrintLine(TEXT("The hidden word is: %s"), *HiddenWord); // Debug line

}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again..."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
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
        PrintLine(TEXT("Your guess is the wrong length\nThe hidden word is %i-letters long"), HiddenWord.Len());
        return;
    } 

    // Guess has repeating letters (i.e. not an isogram)
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("Your guess has repeating letters, try again!"));
        return;
    }

    PrintLine(TEXT("You have lost a life"));

    if (--Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left...\nThe hidden word was: %s\nGAME OVER"), *HiddenWord);
        EndGame();
        return; 
    }

    // Show the player Bulls and Cows
    FBullCowCount Score = GetBullCows(Guess);

    PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);

    PrintLine(TEXT("Guess again, you have %i lives remaining"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word)
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

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }

        for (int32 HiddenWordIndex = 0; HiddenWordIndex < HiddenWord.Len(); HiddenWordIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenWordIndex])
            {
                Count.Cows++;
                break;
            }
        }
    }

    return Count;
}