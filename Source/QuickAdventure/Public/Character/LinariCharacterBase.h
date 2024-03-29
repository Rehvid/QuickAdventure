// Copyright Dawid Harendarz.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LinariCharacterBase.generated.h"

UCLASS(Abstract)
class QUICKADVENTURE_API ALinariCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ALinariCharacterBase();

protected:
	virtual void BeginPlay() override;
};
