// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatfromerGameMode.h"

void APlatfromerGameMode::StartPlay()
{
	Super::StartPlay();

	SetGameState(EGameState::InProgress);
}

void APlatfromerGameMode::SetGameState(EGameState State)
{
	if (CurrentGameState == State) return;

	CurrentGameState = State;
	GameState.Broadcast(CurrentGameState);
}

void APlatfromerGameMode::GameOver()
{
	SetGameState(EGameState::GameOver);
}
