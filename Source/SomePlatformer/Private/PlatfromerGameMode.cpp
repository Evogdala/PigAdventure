// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatfromerGameMode.h"

void APlatfromerGameMode::StartPlay()
{
	Super::StartPlay();

	SetGameState(EGameState::InProgress);
}

bool APlatfromerGameMode::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	const bool PauseSet = Super::SetPause(PC, CanUnpauseDelegate);

	if (PauseSet)
	{
		SetGameState(EGameState::Pause);
	}

	return PauseSet;
}

bool APlatfromerGameMode::ClearPause()
{
	const bool PauseCleared = Super::ClearPause();

	if (PauseCleared)
	{
		SetGameState(EGameState::InProgress);
	}

	return PauseCleared;
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
