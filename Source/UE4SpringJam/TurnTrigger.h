// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeatReact.h"
#include "IceReact.h"
#include "TurnTrigger.generated.h"

UCLASS()
class UE4SPRINGJAM_API ATurnTrigger : public AActor, public IHeatReact, public IIceReact
{
	GENERATED_BODY()
	
public:	
	ATurnTrigger();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void Heat() override;
	virtual void Ice() override;

	class UMeshComponent* mesh;

	UPROPERTY(EditAnywhere)
	AActor* connectedActor;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* heatMaterialDecal;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* iceMaterialDecal;
};
