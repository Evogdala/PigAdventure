// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PlatformerOverlay.h"
#include "Components/TextBlock.h"

void UPlatformerOverlay::SetScore(int32 Score)
{
	if (!ScoreCount) return;

	const FString PointsString = FString::Printf(TEXT("%d"), Score);
	const FText PointsText = FText::FromString(PointsString);
	ScoreCount->SetText(PointsText);
}

void UPlatformerOverlay::SetLives(int32 Lives)
{
	if (!LivesCount) return;

	const FString LivesString = FString::Printf(TEXT("%d"), Lives);
	const FText LivesText = FText::FromString(LivesString);
	LivesCount->SetText(LivesText);
}
