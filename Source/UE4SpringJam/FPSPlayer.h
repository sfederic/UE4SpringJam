// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WidgetScanning.h"
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

	//Bind axis funcs
	void MoveForward(float val);
	void MoveRight(float val);
	void LookUp(float val);
	void LookSide(float val);

	//Bind action funcs
	void SetScan();
	void SetNote();
	void Shoot();

	//WIDGET CLASSES
	UPROPERTY(EditAnywhere, Category="Widgets")
	TSubclassOf<UUserWidget> widgetScanningClass;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UUserWidget> widgetMainHUDClass;

	//WIDGET OBJECTS 
	UPROPERTY()
	UWidgetScanning* widgetScanning;

	UPROPERTY()
	UUserWidget* widgetMainHUD;

	//Actor spawn templates
	UPROPERTY(EditAnywhere, Category="Spawn Templates")
	TSubclassOf<class ANoteNode> noteNodeClass;

	//Particle systems
	UPROPERTY(EditAnywhere, Category="Particles")
	class UParticleSystem* particlePlasmaShot;

	//Components
	class UCameraComponent* camera;

	//Structs
	FHitResult scanHit;
	FHitResult noteHit;
	FHitResult shootHit;
	FCollisionQueryParams scanParams;

	//Variables
	float scanDistance = 10000.f;
	bool bIsScanning;
};
