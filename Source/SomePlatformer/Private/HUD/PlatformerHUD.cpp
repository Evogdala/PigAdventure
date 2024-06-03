// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PlatformerHUD.h"
#include "Blueprint/UserWidget.h"
#include "PlatfromerGameMode.h"

void APlatformerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!GetWorld()) return;

	Controller = GetWorld()->GetFirstPlayerController();
	if (!Controller) return;

	Controller->SetInputMode(FInputModeGameOnly());
	Controller->SetShowMouseCursor(false);



	PlatformerOverlay = CreateWidget<UUserWidget>(Controller, PlatformerHUDWidgetClass);
	PlatformerPause = CreateWidget<UUserWidget>(Controller, PauseWidgetClass);

	GameWidgets.Add(EGameState::InProgress, PlatformerOverlay);
	GameWidgets.Add(EGameState::Pause, PlatformerPause);

	for (auto GameWidgetPair : GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if (!GameWidget) continue;

		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	APlatfromerGameMode* GameMode = Cast<APlatfromerGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->GameState.AddUObject(this, &APlatformerHUD::OnGameStateChanged);
	}
}

void APlatformerHUD::OnGameStateChanged(EGameState State)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
		if (CurrentWidget)
		{

			CurrentWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
