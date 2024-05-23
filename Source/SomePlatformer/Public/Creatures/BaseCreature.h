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
class UBoxComponent;

UCLASS()
class SOMEPLATFORMER_API ABaseCreature : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCreature();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Movement, meta = (ClampMin = 10.0, ClampMax = 1000.0))
	float MinSpeed = 400.0f;

	UPROPERTY(EditAnywhere, Category = Movement, meta = (ClampMin = 10.0, ClampMax = 1000.0))
	float SpeedBoost = 200.0f;

	UPROPERTY(EditAnywhere, Category = Movement, meta = (ClampMin = 2.0, ClampMax = 20.0))
	float SpeedIncrease = 15.0f;

	UFUNCTION()
	virtual void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Box;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* PlatformerMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DashAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int32 Score;

	void Move(const FInputActionValue& Value);
	void StopMoving(const FInputActionValue& Value);
	void Turning(const FInputActionValue& Value);
	void Dash(const FInputActionValue& Value);
	void StopDashing(const FInputActionValue& Value);

	void DashHandle(bool bIsSupposeToDash);

	bool bIsFacingForward = true;
	bool bIsDashing = false;
	bool bIsMoving = false;

	float MaxSpeed;

public:
	FORCEINLINE void SetScore(const int32 Points) { Score += Points; }
	FORCEINLINE int32 GetScore() { return Score; }
};
