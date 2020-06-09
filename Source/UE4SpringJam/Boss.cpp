// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"
#include "DestructibleComponent.h"

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

void ABoss::Heat()
{
	//FindComponentByClass<UDestructibleComponent>()->ApplyDamage(1000.f, GetActorLocation(), GetActorForwardVector(), 1000.f);
}

