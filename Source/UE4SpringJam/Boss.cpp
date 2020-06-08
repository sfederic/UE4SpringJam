// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"

ABoss::ABoss()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABoss::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

