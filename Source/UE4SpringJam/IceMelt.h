// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeatReact.h"
#include "IceReact.h"
#include "IceMelt.generated.h"

UCLASS()
class UE4SPRINGJAM_API AIceMelt : public AActor, public IHeatReact, public IIceReact
{
	GENERATED_BODY()
	
public:	
	AIceMelt();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void Heat() override;
	virtual void Ice() override;

	UPROPERTY(EditAnywhere)
	FVector scaleRate;

	class UParticleSystemComponent* particle;

	bool bIsMelting = false;
};
