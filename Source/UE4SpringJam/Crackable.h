// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeatReact.h"
#include "Crackable.generated.h"

//Class for using heat crack material( might to it on the ice too, reparent)

UCLASS()
class UE4SPRINGJAM_API ACrackable : public AActor, public IHeatReact
{
	GENERATED_BODY()
	
public:	
	ACrackable();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void Heat() override;

	class UDestructibleComponent* dc;

	UPROPERTY(EditAnywhere)
	USoundBase* breakSound;

	UPROPERTY(EditAnywhere)
	float crackIncrement;

	float crackVal = 0.f;
};
