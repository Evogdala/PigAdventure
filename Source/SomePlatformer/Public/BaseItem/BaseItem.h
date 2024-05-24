// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

class USphereComponent;
class UNiagaraSystem;

UCLASS()
class SOMEPLATFORMER_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseItem();
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

	void SpawnNiagaraSystem(UNiagaraSystem* NiagaraSystem) const;
	void PlaySound(USoundBase* Sound) const;

};
