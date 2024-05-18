// Copyright Dawid Harendarz.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class QUICKADVENTURE_API AEnemyCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	virtual void GetHit() override;
};
