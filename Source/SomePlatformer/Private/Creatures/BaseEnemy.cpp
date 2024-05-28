// Fill out your copyright notice in the Description page of Project Settings.


#include "Creatures/BaseEnemy.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveHorizontally();
}
