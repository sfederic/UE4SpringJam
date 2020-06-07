// Fill out your copyright notice in the Description page of Project Settings.


#include "Water.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSPlayer.h"
#include "Particles/ParticleSystemComponent.h"

AWater::AWater()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AWater::BeginPlay()
{
	Super::BeginPlay();
	
	box = FindComponentByClass<UBoxComponent>();
	box->OnComponentBeginOverlap.AddDynamic(this, &AWater::StopSnow);
	box->OnComponentEndOverlap.AddDynamic(this, &AWater::StartSnow);
}

void AWater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWater::StartSnow(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AFPSPlayer* player = Cast<AFPSPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (player)
	{
		player->particleSystems[player->snowParticleIndex]->SetActive(true);
		UE_LOG(LogTemp, Warning, TEXT("Snow on"));
	}
}

void AWater::StopSnow(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFPSPlayer* player = Cast<AFPSPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (player)
	{
		player->particleSystems[player->snowParticleIndex]->SetActive(false);
		UE_LOG(LogTemp, Warning, TEXT("Snow off"));
	}
}
