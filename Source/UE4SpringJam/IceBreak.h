// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IceBreak.generated.h"

UCLASS()
class UE4SPRINGJAM_API AIceBreak : public AActor
{
	GENERATED_BODY()
	
public:	
	AIceBreak();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	class UDestructibleComponent* dc;
};
