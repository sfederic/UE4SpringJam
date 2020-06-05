// Fill out your copyright notice in the Description page of Project Settings.


#include "NoteNode.h"
#include "Components/WidgetComponent.h"

ANoteNode::ANoteNode()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ANoteNode::BeginPlay()
{
	Super::BeginPlay();
	
	widgetComponent = FindComponentByClass<UWidgetComponent>();
}

void ANoteNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

