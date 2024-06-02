// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Pause.generated.h"

class UButton;
class UPlatformerGameInstance;

UCLASS()
class SOMEPLATFORMER_API UPause : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UButton* MenuButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RetryButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

private:
	UFUNCTION()
	void OnMenu();

	UFUNCTION()
	void OnRetryGame();

	UFUNCTION()
	void OnEndGame();

	UPROPERTY()
	const UPlatformerGameInstance* GameInstance;
};
