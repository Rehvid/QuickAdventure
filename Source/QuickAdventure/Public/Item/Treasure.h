// Copyright Dawid Harendarz.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemBase.h"
#include "Treasure.generated.h"

/**
 * 
 */
UCLASS()
class QUICKADVENTURE_API ATreasure : public AItemBase
{
	GENERATED_BODY()

public:
	ATreasure();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
