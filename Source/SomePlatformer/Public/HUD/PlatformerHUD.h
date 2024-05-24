// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlatformerHUD.generated.h"

UCLASS()
class SOMEPLATFORMER_API APlatformerHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UUserWidget> PlatformerHUD;

	UPROPERTY()
	UUserWidget* PlatformerOverlay;

	UPROPERTY()
	APlayerController* Controller;

public:
	FORCEINLINE UUserWidget* GetPlatformerOverlay() const { return PlatformerOverlay; }
};
