#pragma once

#include "Engine/DataTable.h"
#include "Containers/UnrealString.h" 
#include "ConvoData.generated.h"

USTRUCT(BlueprintType)
struct FConvoData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString text;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name;
};