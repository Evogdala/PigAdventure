// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MenuHUD.h"
#include "Blueprint/UserWidget.h"

void AMenuHUD::BeginPlay()
{
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	UUserWidget* PlatformerMenu = CreateWidget<UUserWidget>(Controller, MenuHUDWidgetClass);
	if (Controller && PlatformerMenu)
	{
		PlatformerMenu->AddToViewport();
	}
}
