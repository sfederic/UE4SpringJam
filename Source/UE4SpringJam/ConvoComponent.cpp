// Fill out your copyright notice in the Description page of Project Settings.


#include "ConvoComponent.h"

UConvoComponent::UConvoComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UConvoComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UConvoComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

