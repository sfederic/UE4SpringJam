// Fill out your copyright notice in the Description page of Project Settings.


#include "MonumentManager.h"
#include "Kismet/GameplayStatics.h"
#include "Crackable.h"

AMonumentManager::AMonumentManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMonumentManager::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACrackable::StaticClass(), monuments);
}

void AMonumentManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

