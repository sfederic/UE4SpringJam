// Fill out your copyright notice in the Description page of Project Settings.


#include "IceTrigger.h"
#include "IceBreak.h"

AIceTrigger::AIceTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AIceTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void AIceTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIceTrigger::Ice()
{
	if (linkedActor)
	{
		AIceBreak* ice = Cast<AIceBreak>(linkedActor);
		if (ice)
		{
			ice->Heat();
		}
	}
}
