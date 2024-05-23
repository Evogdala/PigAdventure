// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem/PickupItem.h"

#include "Components/SphereComponent.h"

#include "Creatures/BaseCreature.h"

APickupItem::APickupItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;

	AddActorWorldRotation(FRotator(0.0f, 14.0f * DeltaTime, 0.0f));
	AddActorWorldOffset(FVector(0.0f, 0.0f, TransformedSine()));
}

void APickupItem::BeginPlay()
{
	Super::BeginPlay();

	ItemSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::OnSphereOverlap);
}

void APickupItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABaseCreature* Creature = Cast<ABaseCreature>(OtherActor))
	{
		Creature->SetScore(Points);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.0f, FColor::Red, FString::Printf(TEXT("Score: %d"), Creature->GetScore()));
		Destroy();
	}
}

float APickupItem::TransformedSine()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant); // period = 2*pi/k
}
