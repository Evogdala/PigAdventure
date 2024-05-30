// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "PlatformerGameInstance.h"

void UMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	MenuSetup();

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UMenu::OnStartGame);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UMenu::OnEndGame);
	}
}

void UMenu::MenuSetup()
{
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	if (GetWorld())
	{
		APlayerController* Controller = GetWorld()->GetFirstPlayerController();
		if (Controller)
		{
			/*FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);*/
			Controller->SetInputMode(FInputModeUIOnly());
			Controller->SetShowMouseCursor(true);
		}
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
