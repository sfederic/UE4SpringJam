// Fill out your copyright notice in the Description page of Project Settings.

#include "IceMelt.h"
#include "Misc/App.h"
#include "Particles/ParticleSystemComponent.h"

AIceMelt::AIceMelt()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AIceMelt::BeginPlay()
{
	Super::BeginPlay();
	particle = FindComponentByClass<UParticleSystemComponent>();
	particle->SetActive(false);
}

void AIceMelt::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMelting)
	{
		particle->SetActive(true); 
	}
	else if(!bIsMelting)
	{
		particle->SetActive(false);
	}
}

void AIceMelt::Heat()
{
	FVector scale = GetActorScale3D();
	if (scale.X > 1.0f)
	{
		scale -= scaleRate * FApp::GetDeltaTime();
		bIsMelting = true;
	}
	else
	{
		bIsMelting = false;
	}

	SetActorScale3D(scale);
}

void AIceMelt::Ice()
{
	FVector scale = GetActorScale3D();
	if (scale.X < 4.f)
	{
		scale += scaleRate * FApp::GetDeltaTime();;
	}
	SetActorScale3D(scale);
}
