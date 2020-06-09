// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4SPRINGJAM_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int bossCountdown = 300; //5 minutes

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int monumentsDestroyedCounter = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bNoteActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bBossTimer = false;
};
