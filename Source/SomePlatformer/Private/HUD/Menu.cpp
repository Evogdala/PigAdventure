// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "PlatformerGameInstance.h"

void UMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	MenuSetup();
}

void UMenu::MenuSetup()
{
	if (GetWorld())
	{
		APlayerController* Controller = GetWorld()->GetFirstPlayerController();
		if (Controller)
		{
			Controller->SetInputMode(FInputModeUIOnly());
			Controller->SetShowMouseCursor(true);
		}
	}

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UMenu::OnStartGame);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UMenu::OnEndGame);
	}
}

void UMenu::OnStartGame()
{
	if (!GetWorld()) return;

	const UPlatformerGameInstance* GameInstance = GetWorld()->GetGameInstance<UPlatformerGameInstance>();
	if (GameInstance && !GameInstance->GetStartupLevelName().IsNone())
	{
		UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevelName());
	}
}

void UMenu::OnEndGame()
{

}
