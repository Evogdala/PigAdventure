// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem/SavePoint.h"

#include "Components/SphereComponent.h"

#include "Creatures/BaseCreature.h"

void ASavePoint::BeginPlay()
{
	Super::BeginPlay();

	ItemSphere->OnComponentBeginOverlap.AddDynamic(this, &ASavePoint::OnSphereOverlap);
}

void ASavePoint::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABaseCreature* Creature = Cast<ABaseCreature>(OtherActor))
	{
		Creature->SetLastSavePointLocation(GetActorLocation());
	}
}
