// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to the Bull Cow Game!"));
    PrintLine(TEXT("Please guess the 4-letter word, and press 'Enter'")); // TODO remove the magic num

    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    // Checking player's guess

    if (HiddenWord == Input) {
        PrintLine(TEXT("I'M GONNA EAT YOUR BUTT"));
    } else {
        PrintLine(TEXT("RIP you are getting pegged..."));
    }
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("cake");
    Lives = 4; 
}
