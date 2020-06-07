// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnIceBlock.h"
#include "TimerManager.h" 

ASpawnIceBlock::ASpawnIceBlock()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASpawnIceBlock::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle, this, &ASpawnIceBlock::DestroyOnTimer, 0.1f, false);
}

void ASpawnIceBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bStartDestroyTimer)
	{
		destroyTimer += FApp::GetDeltaTime();

		if (destroyTimer > 10.f)
		{
			FVector scale = GetActorScale3D();
			scale -= FVector(0.01f);
			SetActorScale3D(scale);

			if (scale.X < 0.1f)
			{
				Destroy();
			}
		}
	}
}

void ASpawnIceBlock::Heat()
{
	Destroy();
}

void ASpawnIceBlock::DestroyOnTimer()
{
	bStartDestroyTimer = true;
}
