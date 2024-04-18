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
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnOverlap(AActor* TargetActor) override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Treasure Properties")
	int32 Gold;
};
