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
	TArray<FPatrolPoint> NewPatrolPath;
	for (const FPatrolPoint& Patrol : PatrolPath)
	{
		if (CurrentPatrolPoint != Patrol.PatrolPoint)
		{
			NewPatrolPath.Add(Patrol);
		}
	}

	const int32 PatrolPathLength = NewPatrolPath.Num();
	const int32 Selection = FMath::RandRange(0, PatrolPathLength - 1);
	const FPatrolPoint CurrentPatrol = NewPatrolPath[Selection];
	CurrentPatrolPoint = CurrentPatrol.PatrolPoint;

	return CurrentPatrol;
}


void ABaseEnemy::SetCharacterWalkSpeed() const
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	}
}

void ABaseEnemy::SetCharacterChaseSpeed() const
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = MaxChaseSpeed;
	}
}




