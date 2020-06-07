// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonumentManager.generated.h"

UCLASS()
class UE4SPRINGJAM_API AMonumentManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AMonumentManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	TArray<AActor*> monuments;
};
