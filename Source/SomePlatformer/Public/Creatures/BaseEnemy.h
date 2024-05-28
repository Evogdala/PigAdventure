// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem/DeadlyObject.h"
#include "BaseEnemy.generated.h"

UCLASS()
class SOMEPLATFORMER_API ABaseEnemy : public ADeadlyObject
{
	GENERATED_BODY()
	
public:
	ABaseEnemy();
	virtual void Tick(float DeltaTime) override;
};
