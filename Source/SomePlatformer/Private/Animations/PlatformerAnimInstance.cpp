// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/PlatformerAnimInstance.h"

#include "Creatures/BaseCreature.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlatformerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PlatformerCharacter = Cast<ABaseCreature>(TryGetPawnOwner());
}

void UPlatformerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (!PlatformerCharacter) return;


	bIsInAir = PlatformerCharacter->GetCharacterMovement()->IsFalling();
}