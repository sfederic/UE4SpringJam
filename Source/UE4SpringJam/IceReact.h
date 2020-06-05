#pragma once

#include "IceReact.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UIceReact : public UInterface
{
    GENERATED_BODY()
};

class IIceReact
{
    GENERATED_BODY()

public:
    virtual void Ice() = 0;
};