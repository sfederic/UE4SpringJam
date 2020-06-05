// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NoteNode.generated.h"

UCLASS()
class UE4SPRINGJAM_API ANoteNode : public AActor
{
	GENERATED_BODY()
	
public:	
	ANoteNode();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* widgetComponent;
};
