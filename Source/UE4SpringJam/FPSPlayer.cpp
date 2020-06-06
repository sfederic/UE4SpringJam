// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSPlayer.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "ScanDataComponent.h"
#include "NoteNode.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HeatReact.h"
#include "IceReact.h"
#include "DestructibleComponent.h"
#include "Water.h"
#include "SpawnIceBlock.h"

AFPSPlayer::AFPSPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	scanParams.AddIgnoredActor(this);
}

void AFPSPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	camera = FindComponentByClass<UCameraComponent>();
	check(camera);

	//UI Setup
	widgetMainHUD = CreateWidget<UUserWidget>(GetWorld(), widgetMainHUDClass);
	if (widgetMainHUD)
	{
		widgetMainHUD->AddToViewport();
	}

	widgetScanning = CreateWidget<UWidgetScanning>(GetWorld(), widgetScanningClass);
	if (widgetScanning)
	{
		widgetScanning->scanName = TEXT("No Name");
		widgetScanning->scanText = TEXT("No Data");
	}

	//Particles
	GetComponents<UParticleSystemComponent>(particleSystems);
	for (int i = 0; i < particleSystems.Num(); i++)
	{
		particleSystems[i]->SetActive(false);
	}

	particleSystems[snowParticleIndex]->SetActive(true);
}

void AFPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Movement
	InputComponent->BindAxis("Forward", this, &AFPSPlayer::MoveForward);
	InputComponent->BindAxis("Back", this, &AFPSPlayer::MoveForward);
	InputComponent->BindAxis("Right", this, &AFPSPlayer::MoveRight);
	InputComponent->BindAxis("Left", this, &AFPSPlayer::MoveRight);
	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AFPSPlayer::Jump);

	//Looking
	InputComponent->BindAxis("Mouse X", this, &AFPSPlayer::LookSide);
	InputComponent->BindAxis("Mouse Y", this, &AFPSPlayer::LookUp);

	//Other Actions/Axis
	InputComponent->BindAction("SetScan", EInputEvent::IE_Pressed, this, &AFPSPlayer::SetScan);
	InputComponent->BindAction("SetNote", EInputEvent::IE_Pressed, this, &AFPSPlayer::SetNote);
	InputComponent->BindAction("DeleteNote", EInputEvent::IE_Pressed, this, &AFPSPlayer::DeleteLastNote);
	InputComponent->BindAxis("ShootHeat", this, &AFPSPlayer::ShootHeat);
	InputComponent->BindAxis("ShootIce", this, &AFPSPlayer::ShootIce);
}

void AFPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Scanning
	if (bIsScanning)
	{
		if (GetWorld()->LineTraceSingleByChannel(scanHit, camera->GetComponentLocation(),
			camera->GetComponentLocation() + (camera->GetForwardVector() * scanDistance), ECC_WorldStatic, scanParams))
		{
			UScanDataComponent* scanData = scanHit.GetActor()->FindComponentByClass<UScanDataComponent>();
			if (scanData)
			{
				widgetScanning->scanName = scanData->scanName;
				widgetScanning->scanText = scanData->scanText;
			}
			else
			{
				widgetScanning->scanName = TEXT("No Name");
				widgetScanning->scanText = TEXT("No Scan Data");
			}
		}
		else
		{
			widgetScanning->scanName = TEXT("No Name");
			widgetScanning->scanText = TEXT("No Scan Data");
		}
	}
}

void AFPSPlayer::MoveForward(float val)
{
	FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(dir, val * moveSpeed);
}

void AFPSPlayer::MoveRight(float val)
{
	FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(dir, val * moveSpeed);
}

void AFPSPlayer::LookUp(float val)
{
	AddControllerPitchInput(val);
}

void AFPSPlayer::LookSide(float val)
{
	AddControllerYawInput(val);
}

void AFPSPlayer::SetScan()
{
	bIsScanning = !bIsScanning;

	if (bIsScanning && !widgetScanning->IsInViewport())
	{
		widgetScanning->AddToViewport();
	}
	else if (!bIsScanning && widgetScanning->IsInViewport())
	{
		widgetScanning->RemoveFromViewport();
	}
}

void AFPSPlayer::SetNote()
{
	if (GetWorld()->LineTraceSingleByChannel(noteHit, camera->GetComponentLocation(),
		camera->GetComponentLocation() + (camera->GetForwardVector() * scanDistance), ECC_WorldStatic, scanParams))
	{
		FTransform transform = FTransform();
		transform.SetLocation(noteHit.ImpactPoint);
		transform.SetRotation(FQuat(noteHit.ImpactNormal.Rotation()));
		ANoteNode* noteNode = GetWorld()->SpawnActor<ANoteNode>(noteNodeClass, transform);
		if (noteNode)
		{
			notesInLevel.Add(noteNode);
		}
	}
}

void AFPSPlayer::ShootHeat(float val)
{
	if (val)
	{
		particleSystems[heatBeamIndex]->SetActive(true);
		particleSystems[heatBeamSparksIndex]->SetActive(true);

		if (GetWorld()->LineTraceSingleByChannel(shootHit, particleSystems[heatBeamIndex]->GetComponentLocation(),
			particleSystems[heatBeamIndex]->GetComponentLocation() + (camera->GetForwardVector() * 10000.f), ECC_WorldStatic, scanParams))
		{
			particleSystems[heatBeamIndex]->SetBeamSourcePoint(0, particleSystems[heatBeamIndex]->GetComponentLocation(), 0);
			particleSystems[heatBeamIndex]->SetBeamTargetPoint(0, shootHit.ImpactPoint, 0);

			particleSystems[heatBeamSparksIndex]->SetWorldLocation(shootHit.ImpactPoint);

			UGameplayStatics::SpawnDecalAtLocation(GetWorld(), heatShotDecal, FVector(10.f), shootHit.ImpactPoint + FVector(0.f, 0.f, 1.f), 
				FRotator(-90.f, 0.f,0.f), 1.5f);

			//Heat effects
			IHeatReact* heatReact = Cast<IHeatReact>(shootHit.GetActor());
			if (heatReact)
			{
				heatReact->Heat();
				return; //TODO: Good for now, not good for later
			}

			UDestructibleComponent* dc = shootHit.GetActor()->FindComponentByClass<UDestructibleComponent>();
			if (dc)
			{
				dc->ApplyDamage(destructionDamageAmount, shootHit.ImpactPoint, camera->GetForwardVector(), destructionImpulseStrength);
			}
		}
		else
		{
			//If no target (eg. shoot into air)
			particleSystems[heatBeamIndex]->SetBeamSourcePoint(0, particleSystems[heatBeamIndex]->GetComponentLocation(), 0);
			particleSystems[heatBeamIndex]->SetBeamTargetPoint(0, particleSystems[heatBeamIndex]->GetComponentLocation() + (camera->GetForwardVector() * 10000.f), 0);

			particleSystems[heatBeamSparksIndex]->SetActive(false);
		}
	}
	else
	{
		particleSystems[heatBeamIndex]->SetBeamSourcePoint(0, particleSystems[heatBeamIndex]->GetComponentLocation(), 0);
		particleSystems[heatBeamIndex]->SetBeamTargetPoint(0, particleSystems[heatBeamIndex]->GetComponentLocation(), 0);

		particleSystems[heatBeamSparksIndex]->SetActive(false);
	}
}

void AFPSPlayer::ShootIce(float val)
{
	if (val)
	{
		particleSystems[iceBeamIndex]->SetActive(true);

		if (GetWorld()->LineTraceSingleByChannel(shootHit, particleSystems[iceBeamIndex]->GetComponentLocation(),
			particleSystems[iceBeamIndex]->GetComponentLocation() + (camera->GetForwardVector() * 10000.f), ECC_GameTraceChannel1, scanParams))
		{
			particleSystems[iceBeamIndex]->SetBeamSourcePoint(0, particleSystems[iceBeamIndex]->GetComponentLocation(), 0);
			particleSystems[iceBeamIndex]->SetBeamTargetPoint(0, shootHit.ImpactPoint, 0);

			//Spawn ice blocks in water
			if (shootHit.GetActor()->IsA<AWater>())
			{
				FTransform trans = {};
				trans.SetLocation(shootHit.ImpactPoint);
				trans.SetRotation(FQuat::Identity);
				GetWorld()->SpawnActor<ASpawnIceBlock>(iceBlockSpawnClass, trans);
			}
		}
		if (GetWorld()->LineTraceSingleByChannel(shootHit, particleSystems[iceBeamIndex]->GetComponentLocation(),
			particleSystems[iceBeamIndex]->GetComponentLocation() + (camera->GetForwardVector() * 10000.f), ECC_WorldStatic, scanParams))
		{
			particleSystems[iceBeamIndex]->SetBeamSourcePoint(0, particleSystems[iceBeamIndex]->GetComponentLocation(), 0);
			particleSystems[iceBeamIndex]->SetBeamTargetPoint(0, shootHit.ImpactPoint, 0);

			//Ice Effects
			IIceReact* iceReact = Cast<IIceReact>(shootHit.GetActor());
			if (iceReact)
			{
				iceReact->Ice();
			}
		}
		else
		{
			particleSystems[iceBeamIndex]->SetBeamSourcePoint(0, particleSystems[iceBeamIndex]->GetComponentLocation(), 0);
			particleSystems[iceBeamIndex]->SetBeamTargetPoint(0, particleSystems[iceBeamIndex]->GetComponentLocation() + (camera->GetForwardVector() * 10000.f), 0);
		}
	}
	else
	{
		particleSystems[iceBeamIndex]->SetBeamSourcePoint(0, particleSystems[iceBeamIndex]->GetComponentLocation(), 0);
		particleSystems[iceBeamIndex]->SetBeamTargetPoint(0, particleSystems[iceBeamIndex]->GetComponentLocation(), 0);
	}
}

void AFPSPlayer::DeleteLastNote()
{
	if (notesInLevel.Num() > 0)
	{
		const int lastElement = notesInLevel.Num() - 1;
		notesInLevel[lastElement]->Destroy();
		notesInLevel.Pop();
	}
}
