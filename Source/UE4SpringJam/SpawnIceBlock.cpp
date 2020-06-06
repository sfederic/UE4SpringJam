// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnIceBlock.h"
#include "TimerManager.h" 

ASpawnIceBlock::ASpawnIceBlock()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ASpawnIceBlock::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle, this, &ASpawnIceBlock::DestroyOnTimer, 10.f, false);
}

void ASpawnIceBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnIceBlock::Heat()
{
	Destroy();
}

void ASpawnIceBlock::DestroyOnTimer()
{
	Destroy();
}
