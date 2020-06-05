// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSPlayer.h"
#include "Engine/World.h"


AFPSPlayer::AFPSPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AFPSPlayer::BeginPlay()
{
	Super::BeginPlay();
	
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
}

void AFPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//Movement
	InputComponent->BindAxis("Forward", this, &AFPSPlayer::MoveForward);
	InputComponent->BindAxis("Back", this, &AFPSPlayer::MoveForward);
	InputComponent->BindAxis("Right", this, &AFPSPlayer::MoveRight);
	InputComponent->BindAxis("Left", this, &AFPSPlayer::MoveRight);
	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this,&AFPSPlayer::Jump);

	//Looking
	InputComponent->BindAxis("Mouse X", this, &AFPSPlayer::LookSide);
	InputComponent->BindAxis("Mouse Y", this, &AFPSPlayer::LookUp);

	//Other Actions
	InputComponent->BindAction("SetScan", EInputEvent::IE_Pressed, this, &AFPSPlayer::SetScan);
}

void AFPSPlayer::MoveForward(float val)
{
	FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(dir, val);
}

void AFPSPlayer::MoveRight(float val)
{
	FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(dir, val);
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
