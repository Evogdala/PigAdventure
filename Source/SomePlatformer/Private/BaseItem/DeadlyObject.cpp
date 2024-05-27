// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem/DeadlyObject.h"

#include "Components/BoxComponent.h"

#include "Creatures/BaseCreature.h"

ADeadlyObject::ADeadlyObject()
{
	PrimaryActorTick.bCanEverTick = false;

	ObjectBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(ObjectBox);

	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	ObjectMesh->SetupAttachment(GetRootComponent());
}

void ADeadlyObject::BeginPlay()
{
	Super::BeginPlay();
	
	ObjectBox->OnComponentBeginOverlap.AddDynamic(this, &ADeadlyObject::OnBoxOverlap);
}

void ADeadlyObject::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABaseCreature* Creature = Cast<ABaseCreature>(OtherActor))
	{
		Creature->Death();
	}
}


