// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IceReact.h"
#include "HeatReact.h"
#include "SnowBall.generated.h"

//Ball for shrinking and growing with beams

UCLASS()
class UE4SPRINGJAM_API ASnowBall : public AActor, public IIceReact, public IHeatReact
{
	GENERATED_BODY()
	
public:	
	ASnowBall();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void Heat() override;
	virtual void Ice() override;

	UPROPERTY(EditAnywhere)
	FVector scaleSpeed;
};
