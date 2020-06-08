// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnTrigger.h"
#include "Crackable.h"
#include "Components/MeshComponent.h"
#include "Components/DecalComponent.h" 
#include "IceMelt.h"
#include "SnowBall.h"

ATurnTrigger::ATurnTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATurnTrigger::BeginPlay()
{
	Super::BeginPlay();
	mesh = FindComponentByClass<UMeshComponent>();
}

void ATurnTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurnTrigger::Ice()
{
	mesh->SetVectorParameterValueOnMaterials(TEXT("Colour"), FVector(0.f, 0.f, 1.f));

	TArray<UDecalComponent*> decals;
	GetComponents<UDecalComponent>(decals);
	for (int i = 0; i < decals.Num(); i++)
	{
		decals[i]->SetMaterial(0, iceMaterialDecal);
	}

	if (connectedActor)
	{
		ASnowBall* snowball = Cast<ASnowBall>(connectedActor);
		if (snowball)
		{
			snowball->Ice();
		}
	}
}

void ATurnTrigger::Heat()
{
	mesh->SetVectorParameterValueOnMaterials(TEXT("Colour"), FVector(1.f, 0.f, 0.f));

	TArray<UDecalComponent*> decals;
	GetComponents<UDecalComponent>(decals);
	for (int i = 0; i < decals.Num(); i++)
	{
		decals[i]->SetMaterial(0, heatMaterialDecal);
	}

	if (connectedActor->IsA<ACrackable>())
	{
		ACrackable* crack = Cast<ACrackable>(connectedActor);
		if (crack)
		{
			crack->Heat();
		}
	}
}
