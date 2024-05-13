// Copyright Dawid Harendarz.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class QUICKADVENTURE_API ICombatInterface
{
	GENERATED_BODY()
public:
	
	UFUNCTION()
	virtual void GetHit();
};
