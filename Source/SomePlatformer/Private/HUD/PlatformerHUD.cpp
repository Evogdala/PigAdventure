// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PlatformerHUD.h"
#include "Blueprint/UserWidget.h"

#include "PlatfromerGameMode.h"

void APlatformerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!GetWorld()) return;

	Controller = GetWorld()->GetFirstPlayerController();
	if (Controller && PlatformerHUDWidgetClass)
	{
		PlatformerOverlay = CreateWidget<UUserWidget>(Controller, PlatformerHUDWidgetClass);
		if (PlatformerOverlay)
		{
			PlatformerOverlay->AddToViewport();
		}
	}

	APlatfromerGameMode* GameMode = Cast<APlatfromerGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->GameState.AddUObject(this, &APlatformerHUD::OnGameStateChanged);
	}
}

void APlatformerHUD::OnGameStateChanged(EGameState State)
{

}
