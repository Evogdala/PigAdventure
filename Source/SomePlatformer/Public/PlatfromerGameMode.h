// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlatformerCoreTypes.h"
#include "PlatfromerGameMode.generated.h"

UCLASS()
class SOMEPLATFORMER_API APlatfromerGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void StartPlay() override;
	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
	virtual bool ClearPause() override;

	FGameStateSignature GameState;

private:
	EGameState CurrentGameState = EGameState::WaitingToStart;

	void SetGameState(EGameState State);

	void GameOver();
};
