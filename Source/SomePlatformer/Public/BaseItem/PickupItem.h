// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem/BaseItem.h"
#include "PickupItem.generated.h"

class USphereComponent;
class UNiagaraSystem;

UCLASS()
class SOMEPLATFORMER_API APickupItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	APickupItem();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* ItemSphere;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UNiagaraSystem* PickupEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	USoundBase* PickupSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (ClampMin = 1, ClampMax = 100))
	int32 Points = 15;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SpawnNiagaraSystem(UNiagaraSystem* NiagaraSystem) const;
	void PlaySound(USoundBase* Sound) const;
};
