// Fill out your copyright notice in the Description page of Project Settings.


#include "Crackable.h"
#include "DestructibleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSPlayer.h"
#include "ConvoComponent.h"

ACrackable::ACrackable()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACrackable::BeginPlay()
{
	Super::BeginPlay();
	
	dc = FindComponentByClass<UDestructibleComponent>();
}

void ACrackable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (crackVal >= 1.0f && crackVal < 2.0f)
	{
		dc->ApplyDamage(1000.f, GetActorLocation(), GetActorForwardVector(), 2000.f);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), breakSound, GetActorLocation(), 1.5f, 0.9f);
		AFPSPlayer* player = Cast<AFPSPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (player)
		{
			player->widgetMainHUD->monumentsDestroyedCounter++;
			if (player->widgetMainHUD->monumentsDestroyedCounter < player->finalMonumentCounter)
			{
				//FString context;
				player->intelData = FindComponentByClass<UConvoComponent>()->data;
			}
		}
		crackVal = 2.0f;
	}
}

void ACrackable::Heat()
{
	crackVal += crackIncrement;
	dc->SetScalarParameterValueOnMaterials(TEXT("CrackValue"), crackVal);
}
