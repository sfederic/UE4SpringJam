// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IceReact.h"
#include "IceTrigger.generated.h"

UCLASS()
class UE4SPRINGJAM_API AIceTrigger : public AActor, public IIceReact
{
	GENERATED_BODY()
	
public:	
	AIceTrigger();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void Ice() override;

	UPROPERTY(EditAnywhere)
	AActor* linkedActor;

};
