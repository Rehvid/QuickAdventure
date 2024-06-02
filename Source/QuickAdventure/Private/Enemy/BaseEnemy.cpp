// Copyright Dawid Harendarz.


#include "Enemy/BaseEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

FPatrolPoint ABaseEnemy::TakeRandomPatrolPoint()
{
	//TODO: Make it more random
	const int32 PatrolPathLength = PatrolPath.Num();
	const int32 Selection = FMath::RandRange(0, PatrolPathLength - 1);

	CurrentPatrolPointIndex = Selection;
	return PatrolPath[Selection];
}


