// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeatReact.h"
#include "SpawnIceBlock.generated.h"

UCLASS()
class UE4SPRINGJAM_API ASpawnIceBlock : public AActor, public IHeatReact
{
	GENERATED_BODY()
	
public:	
	ASpawnIceBlock();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void Heat() override;

	void DestroyOnTimer();

};
