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
#include "ConvoWidget.h"
#include "ConvoComponent.h"
#include "Components/WidgetComponent.h"
#include "NoteWidget.h"
#include "Components/AudioComponent.h"

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

	//Audio Setup
	laserAudio = FindComponentByClass<UAudioComponent>();

	//UI Setup
	widgetMainHUD = CreateWidget<UMainHUDWidget>(GetWorld(), widgetMainHUDClass);
	if (widgetMainHUD)
	{
		widgetMainHUD->AddToViewport();
		widgetMainHUD->bNoteActive = false;
	}

	widgetScanning = CreateWidget<UWidgetScanning>(GetWorld(), widgetScanningClass);
	if (widgetScanning)
	{
		widgetScanning->scanName = TEXT("No Name");
		widgetScanning->scanText = TEXT("No Data");
	}

	widgetConvo = CreateWidget<UConvoWidget>(GetWorld(), widgetConvoClass);


	//Particles
	GetComponents<UParticleSystemComponent>(particleSystems);
	for (int i = 0; i < particleSystems.Num(); i++)
	{
		particleSystems[i]->SetActive(false);

		//This is terrible. Make a game in 5 days they said...
		//TODO: ask Epic how they do this properly (multiple FIndComponents)
		FString name = particleSystems[i]->GetName();
		if (name.Compare(TEXT("HeatShot")) == 0)
		{
			heatBeamIndex = i;
		}
		else if (name.Compare(TEXT("IceShot")) == 0)
		{
			iceBeamIndex = i;
		}
		else if (name.Compare(TEXT("HeatShotSparks")) == 0)
		{
			heatBeamSparksIndex = i;
		}
		else if (name.Compare(TEXT("SnowParticle")) == 0)
		{
			snowParticleIndex = i;
		}
		else if (name.Compare(TEXT("IceShotSparks")) == 0)
		{
			iceBeamSparksIndex = i;
		}
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
	InputComponent->BindAxis("ZoomIn", this, &AFPSPlayer::ZoomIn);

	//Other Actions/Axis
	InputComponent->BindAction("SetScan", EInputEvent::IE_Pressed, this, &AFPSPlayer::SetScan);
	InputComponent->BindAction("SetNote", EInputEvent::IE_Pressed, this, &AFPSPlayer::SetNote);
	InputComponent->BindAction("DeleteNote", EInputEvent::IE_Pressed, this, &AFPSPlayer::DeleteLastNote);
	InputComponent->BindAction("Intel", EInputEvent::IE_Pressed, this, &AFPSPlayer::Intel);
	InputComponent->BindAction("ProgressText", EInputEvent::IE_Pressed, this, &AFPSPlayer::ProgressText);
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
				if (previousScanHit.GetActor() != scanHit.GetActor())
				{
					UGameplayStatics::PlaySound2D(GetWorld(), soundScan, 2.0f, 0.75f);
				}

				previousScanHit = scanHit;

				widgetScanning->scanName = scanData->scanName;
				widgetScanning->scanText = scanData->scanText;
			}
			else
			{
				widgetScanning->scanName = TEXT("No Name");
				widgetScanning->scanText = TEXT("No Scan Data");
			}
		}
		else if (GetWorld()->LineTraceSingleByChannel(scanHit, camera->GetComponentLocation(),
			camera->GetComponentLocation() + (camera->GetForwardVector() * scanDistance), ECC_GameTraceChannel1, scanParams))
		{
			UScanDataComponent* scanData = scanHit.GetActor()->FindComponentByClass<UScanDataComponent>();
			if (scanData)
			{
				if (previousScanHit.GetActor() != scanHit.GetActor())
				{
					UGameplayStatics::PlaySound2D(GetWorld(), soundScan);
				}

				previousScanHit = scanHit;

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
	//FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	FVector dir = GetActorForwardVector();
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
	if (bIntel || widgetMainHUD->bNoteActive)
	{
		return;
	}

	bIsScanning = !bIsScanning;

	if (bIsScanning && !widgetScanning->IsInViewport())
	{
		widgetScanning->AddToViewport();
		UGameplayStatics::PlaySound2D(GetWorld(), soundScanOn);
	}
	else if (!bIsScanning && widgetScanning->IsInViewport())
	{
		widgetScanning->RemoveFromViewport();
		UGameplayStatics::PlaySound2D(GetWorld(), soundScanOff);
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
			UNoteWidget* noteWidget = Cast<UNoteWidget>(noteNode->FindComponentByClass<UWidgetComponent>()->GetUserWidgetObject());
			noteWidget->noteLocation = noteHit.ImpactPoint;
			
			UGameplayStatics::PlaySound2D(GetWorld(), soundScanOn, 1.0f, 1.3f);

			notesInLevel.Add(noteNode);

			widgetMainHUD->bNoteActive = true;
		}
	}
}

void AFPSPlayer::ShootHeat(float val)
{
	if (val && !bIntel)
	{
		if (widgetMainHUD->bNoteActive)
		{
			widgetMainHUD->bNoteActive = false;
			return;
		}



		particleSystems[heatBeamIndex]->SetActive(true);
		particleSystems[heatBeamSparksIndex]->SetActive(true);

		if (GetWorld()->LineTraceSingleByChannel(shootHit, particleSystems[heatBeamIndex]->GetComponentLocation(),
			particleSystems[heatBeamIndex]->GetComponentLocation() + (camera->GetForwardVector() * shootDistance), ECC_WorldStatic, scanParams))
		{
			particleSystems[heatBeamIndex]->SetBeamSourcePoint(0, particleSystems[heatBeamIndex]->GetComponentLocation(), 0);
			particleSystems[heatBeamIndex]->SetBeamTargetPoint(0, shootHit.ImpactPoint, 0);

			particleSystems[heatBeamSparksIndex]->SetWorldLocation(shootHit.ImpactPoint);

			FRotator randomRotationOffset = FRotator(FMath::RandRange(0.f, 90.f)); //Looks better than always repeating.
			UGameplayStatics::SpawnDecalAtLocation(GetWorld(), heatShotDecal, FVector(25.f), shootHit.ImpactPoint + FVector(0.f, 0.f, 0.5f), 
				shootHit.ImpactNormal.Rotation() + randomRotationOffset, 3.f);

			//Heat effects
			IHeatReact* heatReact = Cast<IHeatReact>(shootHit.GetActor());
			if (heatReact)
			{
				heatReact->Heat();
				//return; //TODO: Good for now, not good for later
			}

			/*UDestructibleComponent* dc = shootHit.GetActor()->FindComponentByClass<UDestructibleComponent>();
			if (dc)
			{
				dc->ApplyDamage(destructionDamageAmount, shootHit.ImpactPoint, camera->GetForwardVector(), destructionImpulseStrength);
			}*/
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
	if (val && !bIntel)
	{
		if (widgetMainHUD->bNoteActive)
		{
			widgetMainHUD->bNoteActive = false;
			return;
		}


		particleSystems[iceBeamIndex]->SetActive(true);
		particleSystems[iceBeamSparksIndex]->SetActive(true);

		if (GetWorld()->LineTraceSingleByChannel(shootHit, particleSystems[iceBeamIndex]->GetComponentLocation(),
			particleSystems[iceBeamIndex]->GetComponentLocation() + (camera->GetForwardVector() * shootDistance), ECC_GameTraceChannel1, scanParams))
		{
			particleSystems[iceBeamIndex]->SetBeamSourcePoint(0, particleSystems[iceBeamIndex]->GetComponentLocation(), 0);
			particleSystems[iceBeamIndex]->SetBeamTargetPoint(0, shootHit.ImpactPoint, 0);

			particleSystems[iceBeamSparksIndex]->SetWorldLocation(shootHit.ImpactPoint);

			FRotator randomRotationOffset = FRotator(FMath::RandRange(0.f, 90.f));
			UGameplayStatics::SpawnDecalAtLocation(GetWorld(), iceShotDecal, FVector(25.f), shootHit.ImpactPoint + FVector(0.f, 0.f, 0.5f),
				shootHit.ImpactNormal.Rotation() + randomRotationOffset, 3.f);

			//Spawn ice blocks in water
			if (shootHit.GetActor()->IsA<AWater>())
			{
				FTransform trans = {};
				trans.SetLocation(shootHit.ImpactPoint);
				trans.SetRotation(FQuat(FRotator(0.f, FMath::RandRange(0.f, 360.f), 0.f)));
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

			particleSystems[iceBeamSparksIndex]->SetActive(false);
		}
	}
	else
	{
		particleSystems[iceBeamIndex]->SetBeamSourcePoint(0, particleSystems[iceBeamIndex]->GetComponentLocation(), 0);
		particleSystems[iceBeamIndex]->SetBeamTargetPoint(0, particleSystems[iceBeamIndex]->GetComponentLocation(), 0);

		particleSystems[iceBeamSparksIndex]->SetActive(false);
	}
}

void AFPSPlayer::ZoomIn(float val)
{
	if (val)
	{
		camera->FieldOfView -= (zoomSpeed * val);
		camera->FieldOfView = FMath::Clamp(camera->FieldOfView, zoomMin, zoomMax);
	}
}

void AFPSPlayer::ZoomOut(float val)
{
	if (val)
	{
		camera->FieldOfView += (zoomSpeed * val);
		camera->FieldOfView = FMath::Clamp(camera->FieldOfView, zoomMin, zoomMax);
	}
}

void AFPSPlayer::DeleteLastNote()
{
	if (notesInLevel.Num() > 0)
	{
		const int lastElement = notesInLevel.Num() - 1;
		notesInLevel[lastElement]->Destroy();
		notesInLevel.Pop();

		UGameplayStatics::PlaySound2D(GetWorld(), soundScanOff, 1.0f, 0.75f);
	}
}

void AFPSPlayer::Intel()
{
	if (widgetConvo->IsInViewport() == false)
	{
		widgetScanning->RemoveFromViewport();
		bIsScanning = false;
		bIntel = true;

		FHitResult intelHit;
		if (GetWorld()->LineTraceSingleByChannel(intelHit, camera->GetComponentLocation(),
			camera->GetComponentLocation() + (camera->GetForwardVector() * scanDistance), ECC_WorldStatic, scanParams))
		{
			AActor* actor = intelHit.GetActor();
			if (actor)
			{
				UConvoComponent* convo = actor->FindComponentByClass<UConvoComponent>();
				if (convo)
				{
					FString context;
					convo->data->GetAllRows<FConvoData>(context, rows);

					widgetConvo->AddToViewport();

					widgetConvo->name = rows[0]->name;
					widgetConvo->text = rows[0]->text;
				}
			}
		}
	}
}

void AFPSPlayer::ProgressText()
{
	//Do dialogue
	if (bIntel)
	{
		currentIntelIndex++;

		if (currentIntelIndex >= rows.Num())
		{
			bIntel = false;
			widgetConvo->RemoveFromViewport();
		}
		else
		{
			widgetConvo->name = rows[currentIntelIndex]->name;
			widgetConvo->text = rows[currentIntelIndex]->text;
		}
	}
}
