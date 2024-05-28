// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem/PickupItem.h"

#include "Components/SphereComponent.h"

#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Creatures/BaseCreature.h"

APickupItem::APickupItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SetRootComponent(ItemSphere);

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	ItemMesh->SetupAttachment(GetRootComponent());
}

void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddRotation(DeltaTime);
	MoveVertically();
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
		PlaySound(PickupSound);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.0f, FColor::Red, FString::Printf(TEXT("Score: %d"), Creature->GetScore()));
		Destroy();
	}
}

void APickupItem::SpawnNiagaraSystem(UNiagaraSystem* NiagaraSystem) const
{
	if (NiagaraSystem)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, NiagaraSystem, GetActorLocation());
	}
}

void APickupItem::PlaySound(USoundBase* Sound) const
{
	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, this->GetActorLocation());
	}
}