// Fill out your copyright notice in the Description page of Project Settings.


#include "Crackable.h"
#include "DestructibleComponent.h"

ACrackable::ACrackable()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACrackable::BeginPlay()
{
	Super::BeginPlay();
	
	dc = FindComponentByClass<UDestructibleComponent>();
}

void ACrackable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (crackVal >= 1.0f)
	{
		dc->ApplyDamage(1000.f, GetActorLocation(), GetActorForwardVector(), 2000.f);
	}
}

void ACrackable::Heat()
{
	crackVal += crackIncrement;
	dc->SetScalarParameterValueOnMaterials(TEXT("CrackValue"), crackVal);
}
