// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem/BaseItem.h"

#include "Components/SphereComponent.h"

ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = false;

	ItemSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SetRootComponent(ItemSphere);


	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	ItemMesh->SetupAttachment(GetRootComponent());
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

