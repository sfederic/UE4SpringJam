// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSPlayer.generated.h"

UCLASS()
class UE4SPRINGJAM_API AFPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AFPSPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float val);
	void MoveRight(float val);
	void LookUp(float val);
	void LookSide(float val);
};
