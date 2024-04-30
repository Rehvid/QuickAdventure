// Copyright Dawid Harendarz.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

class ALinariCharacter;
class AItemBase;

UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

class QUICKADVENTURE_API IItemInterface
{
	GENERATED_BODY()
public:
	virtual void SetOverlappingItem(AItemBase* Item);
	virtual void HandleInteractionKey(ALinariCharacter* Character);
};
