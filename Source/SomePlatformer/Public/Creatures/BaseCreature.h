// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BaseCreature.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UPlatformerOverlay;

UCLASS()
class SOMEPLATFORMER_API ABaseCreature : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCreature();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetScore(const int32& Points);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Movement, meta = (ClampMin = 10.0, ClampMax = 1000.0))
	float MinSpeed = 400.0f;

	UPROPERTY(EditAnywhere, Category = Movement, meta = (ClampMin = 10.0, ClampMax = 350.0))
	float AdditionalSpeed = 100.0f;

	UPROPERTY(EditAnywhere, Category = Movement, meta = (ClampMin = 10.0, ClampMax = 1000.0))
	float SpeedBoost = 200.0f;

	UPROPERTY(EditAnywhere, Category = Movement, meta = (ClampMin = 2.0, ClampMax = 20.0))
	float SpeedIncrease = 20.0f;

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* PlatformerMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Test Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TestAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int32 Score;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	UPlatformerOverlay* PlatformerOverlay;

	// Inputs
	void Move(const FInputActionValue& Value);
	void StopMoving(const FInputActionValue& Value);
	void Turning(const FInputActionValue& Value);
	void TestPerforming(const FInputActionValue& Value);

	void InitializeOverlay();

	bool bIsFacingForward = true;
	bool bIsDashing = false;
	bool bIsMoving = false;

	float MaxSpeed;
	FVector2D LastVector;
	FVector LastSavePointLocation;

public:
	FORCEINLINE int32 GetScore() { return Score; }
	FORCEINLINE void SetLastSavePointLocation(const FVector& Location) { LastSavePointLocation = Location; }
};
