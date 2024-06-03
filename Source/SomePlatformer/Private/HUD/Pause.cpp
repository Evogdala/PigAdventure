// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Pause.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "PlatformerGameInstance.h"
#include "GameFramework/GameModeBase.h"

void UPause::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GameInstance = GetWorld()->GetGameInstance<UPlatformerGameInstance>();

	PauseSetup();
}

void UPause::PauseSetup()
{

	if (MenuButton)
	{
		MenuButton->OnClicked.AddDynamic(this, &UPause::OnMenu);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UPause::OnEndGame);
	}

	if (RetryButton)
	{
		RetryButton->OnClicked.AddDynamic(this, &UPause::OnRetryGame);
	}

	if (ContinueButton)
	{
		ContinueButton->OnClicked.AddDynamic(this, &UPause::OnContinueGame);
	}
}

void UPause::OnMenu()
{
	if (GameInstance && !GameInstance->GetMenuLevelName().IsNone())
	{
		UGameplayStatics::OpenLevel(this, GameInstance->GetMenuLevelName());
	}
}

void UPause::OnRetryGame()
{
	if (GameInstance && !GameInstance->GetStartupLevelName().IsNone())
	{
		UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevelName());
	}
}

void UPause::OnEndGame()
{
}

void UPause::OnContinueGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}
