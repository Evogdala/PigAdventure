// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlatformerCoreTypes.h"
#include "PlatformerHUD.generated.h"

UCLASS()
class SOMEPLATFORMER_API APlatformerHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UUserWidget> PlatformerHUDWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY()
	UUserWidget* PlatformerOverlay;

	UPROPERTY()
	UUserWidget* PlatformerPause;

	UPROPERTY()
	APlayerController* Controller;

	UPROPERTY()
	TMap<EGameState, UUserWidget*> GameWidgets;

	UPROPERTY()
	UUserWidget* CurrentWidget;

	void OnGameStateChanged(EGameState State);

public:
	FORCEINLINE UUserWidget* GetPlatformerOverlay() const { return PlatformerOverlay; }
};
