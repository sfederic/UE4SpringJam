// Fill out your copyright notice in the Description page of Project Settings.


#include "IceBreak.h"
#include "DestructibleComponent.h"

AIceBreak::AIceBreak()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AIceBreak::BeginPlay()
{
	Super::BeginPlay();
	
	dc = FindComponentByClass<UDestructibleComponent>();
}

void AIceBreak::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
