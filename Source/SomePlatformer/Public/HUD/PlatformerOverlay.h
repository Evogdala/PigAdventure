// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlatformerOverlay.generated.h"

class UTextBlock;

UCLASS()
class SOMEPLATFORMER_API UPlatformerOverlay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetScore(int32 Score);
	void SetLives(int32 Lives);

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreCount;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LivesCount;
};
