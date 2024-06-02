// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlatformerGameInstance.generated.h"

UCLASS()
class SOMEPLATFORMER_API UPlatformerGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditdefaultsOnly, Category = Maps, meta = (AllowPrivateAccess = true))
	FName StartupLevelName = NAME_None;

	UPROPERTY(EditdefaultsOnly, Category = Maps, meta = (AllowPrivateAccess = true))
	FName MenuLevelName = NAME_None;

public:
	FORCEINLINE FName GetStartupLevelName() const { return StartupLevelName; }
	FORCEINLINE FName GetMenuLevelName() const { return MenuLevelName; }
};
