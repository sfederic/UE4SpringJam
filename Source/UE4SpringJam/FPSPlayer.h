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

	void ShootHeat(float val);
	void ShootIce(float val);

	//Bind action funcs
	void SetScan();
	void SetNote();
	void DeleteLastNote();

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

	UPROPERTY(EditAnywhere, Category="Spawn Templates")
	TSubclassOf<class ASpawnIceBlock> iceBlockSpawnClass;

	UPROPERTY(EditAnywhere, Category="Spawn Templates")
	UMaterialInterface* heatShotDecal;

	//Particle systems
	TArray<UParticleSystemComponent*> particleSystems;

	const int heatBeamIndex = 0; //For sure these three will go bad...
	const int iceBeamIndex = 1;
	const int snowParticleIndex = 2;
	const int heatBeamSparksIndex = 3;

	//Components
	class UCameraComponent* camera;

	//Structs
	FHitResult scanHit;
	FHitResult noteHit;
	FHitResult shootHit;
	FCollisionQueryParams scanParams;

	//Variables
	TArray<AActor*> notesInLevel;

	float scanDistance = 10000.f;

	UPROPERTY(EditAnywhere)
	float destructionDamageAmount;

	UPROPERTY(EditAnywhere)
	float destructionImpulseStrength;

	UPROPERTY(EditAnywhere)
	float moveSpeed;

	bool bIsScanning;
};
