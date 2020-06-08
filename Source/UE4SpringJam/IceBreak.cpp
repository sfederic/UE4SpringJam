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

	if (bIsCrackActive)
	{
		crackVal += DeltaTime;
		dc->SetScalarParameterValueOnMaterials("CrackValue", crackVal);

		if (crackVal >= 1.0f)
		{
			dc->ApplyDamage(1000.f, GetActorLocation(), GetActorForwardVector(), 2000.f);
			SetLifeSpan(2.0f);
			bIsCrackActive = false;
		}
	}
}

void AIceBreak::Heat()
{
	bIsCrackActive = true;
}
