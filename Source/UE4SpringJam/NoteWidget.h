// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NoteWidget.generated.h"

/**
 * Note widget for spawning in world at screen space. Majority of work done in Note_BP Event construct
 */
UCLASS()
class UE4SPRINGJAM_API UNoteWidget : public UUserWidget
{
	GENERATED_BODY()
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString noteText;

    UPROPERTY(EditAnywhere, BluePrintReadWrite)
    bool bFirstSpawn = true; //Start it off on true for later mechanics
};
