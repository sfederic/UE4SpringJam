// Fill out your copyright notice in the Description page of Project Settings.

#include "SnowBall.h"
#include "Components/MeshComponent.h"

ASnowBall::ASnowBall()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASnowBall::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASnowBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASnowBall::Heat()
{
	FVector scale = GetActorScale3D();
	if (scale.X > 0.5f) //Scaling is uniform, this is alright
	{
		scale -= scaleSpeed;
		SetActorScale3D(scale);
	}
}

void ASnowBall::Ice()
{
	FVector scale = GetActorScale();
	if (scale.X < 5.0f)
	{
		scale += scaleSpeed;
		SetActorScale3D(scale);
	}
}

