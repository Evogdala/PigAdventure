// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem/SavePoint.h"

#include "Components/SphereComponent.h"

#include "Creatures/BaseCreature.h"

ASavePoint::ASavePoint()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASavePoint::BeginPlay()
{
	Super::BeginPlay();

	ItemSphere->OnComponentBeginOverlap.AddDynamic(this, &ASavePoint::OnSphereOverlap);
	ItemSphere->OnComponentEndOverlap.AddDynamic(this, &ASavePoint::OnSphereEndOverlap);
}

void ASavePoint::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABaseCreature* Creature = Cast<ABaseCreature>(OtherActor))
	{
		SpawnNiagaraSystem(PickupEffect);
		PlaySound(PickupSound);
		Creature->SetLastSavePointLocation(Creature->GetActorLocation());
	}
}

void ASavePoint::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ItemSphere->DestroyComponent();
}
