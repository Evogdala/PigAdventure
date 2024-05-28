// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem/BaseItem.h"


ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = true;


}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;
}

float ABaseItem::TransformedSine()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

void ABaseItem::MoveHorizontally()
{
	AddActorWorldOffset(FVector(TransformedSine(), 0.0f, 0.0f));
}

void ABaseItem::MoveVertically()
{
	AddActorWorldOffset(FVector(0.0f, 0.0f, TransformedSine()));
}

void ABaseItem::AddRotation(const float DeltaTime)
{
	AddActorWorldRotation(FRotator(PitchRot, YawRot, RollRot) * DeltaTime);
}
