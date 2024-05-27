// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeadlyObject.generated.h"

class UBoxComponent;

UCLASS()
class SOMEPLATFORMER_API ADeadlyObject : public AActor
{
	GENERATED_BODY()
	
public:	
	ADeadlyObject();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UPROPERTY(VisibleAnywhere)
	UBoxComponent* ObjectBox;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ObjectMesh;


};
