#pragma once
#include "PlatformerCoreTypes.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	InProgress = 0,
	WaitingToStart,
	Pause,
	GameOver,
	Max
};

DECLARE_MULTICAST_DELEGATE_OneParam(FGameStateSignature, EGameState);