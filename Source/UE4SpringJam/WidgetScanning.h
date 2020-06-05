// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetScanning.generated.h"

/**
 * Widget for scanning the env.
 */
UCLASS()
class UE4SPRINGJAM_API UWidgetScanning : public UUserWidget
{
	GENERATED_BODY()
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString scanText;  
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString scanName;
};
