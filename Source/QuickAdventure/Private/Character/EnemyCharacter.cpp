// Copyright Dawid Harendarz.

#include "Character/EnemyCharacter.h"

void AEnemyCharacter::GetHit(const FVector& ImpactPoint)
{
	HitReaction(ImpactPoint);
}
