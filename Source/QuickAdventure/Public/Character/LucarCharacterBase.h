// Copyright Dawid Harendarz.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LucarCharacterBase.generated.h"

UCLASS(Abstract)
class QUICKADVENTURE_API ALucarCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ALucarCharacterBase();

protected:
	virtual void BeginPlay() override;
};
