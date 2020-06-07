// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WidgetScanning.h"
#include "MainHUDWidget.h"
#include "ConvoWidget.h"
#include "ConvoData.h"
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

	void ZoomIn(float val);
	void ZoomOut(float val);

	//Bind action funcs
	void SetScan();
	void SetNote();
	void DeleteLastNote();
	void Intel();
	void ProgressText();

	//WIDGET CLASSES
	UPROPERTY(EditAnywhere, Category="Widgets")
	TSubclassOf<UUserWidget> widgetScanningClass;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UUserWidget> widgetMainHUDClass;	
	
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UUserWidget> widgetConvoClass;

	//WIDGET OBJECTS 
	UPROPERTY()
	UWidgetScanning* widgetScanning;

	UPROPERTY()
	UMainHUDWidget* widgetMainHUD;	
	
	UPROPERTY()
	UConvoWidget* widgetConvo;

	//Actor spawn templates
	UPROPERTY(EditAnywhere, Category="Spawn Templates")
	TSubclassOf<class ANoteNode> noteNodeClass;

	UPROPERTY(EditAnywhere, Category="Spawn Templates")
	TSubclassOf<class ASpawnIceBlock> iceBlockSpawnClass;

	UPROPERTY(EditAnywhere, Category="Spawn Templates")
	UMaterialInterface* heatShotDecal;

	UPROPERTY(EditAnywhere, Category = "Spawn Templates")
	UMaterialInterface* iceShotDecal;

	//Particle systems
	TArray<UParticleSystemComponent*> particleSystems;

	int heatBeamIndex; //For sure these three will go bad...
	int iceBeamIndex;
	int snowParticleIndex;
	int heatBeamSparksIndex;
	int iceBeamSparksIndex;

	//Sounds
	UPROPERTY(EditAnywhere, Category="Sounds")
	USoundBase* soundScan;	
	
	UPROPERTY(EditAnywhere, Category="Sounds")
	USoundBase* soundScanOn;	

	UPROPERTY(EditAnywhere, Category="Sounds")
	USoundBase* soundScanOff;

	//Components
	class UCameraComponent* camera;

	//Structs
	FHitResult scanHit;
	FHitResult previousScanHit;
	FHitResult noteHit;
	FHitResult shootHit;
	FCollisionQueryParams scanParams;

	//Variables
	TArray<AActor*> notesInLevel;

	UPROPERTY(EditAnywhere)
	float scanDistance;

	UPROPERTY(EditAnywhere)
	float destructionDamageAmount;

	UPROPERTY(EditAnywhere)
	float destructionImpulseStrength;

	UPROPERTY(EditAnywhere)
	float moveSpeed;

	//FOV values
	const float zoomMin = 5.f;
	const float zoomMax = 90.f;

	UPROPERTY(EditAnywhere)
	float zoomSpeed;	
	
	UPROPERTY(EditAnywhere)
	float shootDistance;
	
	//Intel vars
	TArray<FConvoData*> rows;
	int currentIntelIndex = 0;

	bool bIsScanning;
	bool bIntel;
};
