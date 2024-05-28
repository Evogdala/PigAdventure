// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

UCLASS()
class SOMEPLATFORMER_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseItem();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float Amplitude = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float TimeConstant = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sine Parameters")
	float RunningTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation Parameters", meta = (ClampMin = 0.0, ClampMax = 50.0))
	float PitchRot = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation Parameters", meta = (ClampMin = 0.0, ClampMax = 50.0))
	float YawRot = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation Parameters", meta = (ClampMin = 0.0, ClampMax = 50.0))
	float RollRot = 0.0f;

	float TransformedSine();
	void MoveHorizontally();
	void MoveVertically();
	void AddRotation(const float DeltaTime);
};
