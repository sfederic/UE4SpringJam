// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeatReact.h"
#include "IceBreak.generated.h"

UCLASS()
class UE4SPRINGJAM_API AIceBreak : public AActor, public IHeatReact
{
	GENERATED_BODY()
	
public:	
	AIceBreak();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void Heat() override;

	class UDestructibleComponent* dc;

	UPROPERTY(EditAnywhere)
	USoundBase* breakSound;

	float crackVal = 0.f;
	//const float crackIncrement = 0.01f;

	bool bIsCrackActive = false;
};
