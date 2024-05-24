// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PlatformerHUD.h"
#include "Blueprint/UserWidget.h"

void APlatformerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!GetWorld()) return;

	Controller = GetWorld()->GetFirstPlayerController();
	if (Controller && PlatformerHUD)
	{
		PlatformerOverlay = CreateWidget<UUserWidget>(Controller, PlatformerHUD);
		if (PlatformerOverlay)
		{
			PlatformerOverlay->AddToViewport();
		}
	}
}
