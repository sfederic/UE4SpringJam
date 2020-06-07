// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConvoWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4SPRINGJAM_API UConvoWidget : public UUserWidget
{
	GENERATED_BODY()
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString text;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString name;
};
