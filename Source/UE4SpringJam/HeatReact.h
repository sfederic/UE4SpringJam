#pragma once

#include "HeatReact.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UHeatReact : public UInterface
{
    GENERATED_BODY()
};

class IHeatReact
{
    GENERATED_BODY()

public:
    virtual void Heat() = 0;
};