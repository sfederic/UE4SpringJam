// Fill out your copyright notice in the Description page of Project Settings.

#include "ScanDataComponent.h"

UScanDataComponent::UScanDataComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	//scanText = TEXT("No Entry");
	//scanName = TEXT("No Name");
}


void UScanDataComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UScanDataComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

