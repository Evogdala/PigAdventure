// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem/PickupItem.h"
#include "SavePoint.generated.h"

UCLASS()
class SOMEPLATFORMER_API ASavePoint : public APickupItem
{
	GENERATED_BODY()
	
public:
	ASavePoint();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
