// Copyright Dawid Harendarz.

#include "Character/EnemyCharacter.h"

#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AEnemyCharacter::GetHit(const FVector& ImpactPoint)
{
	HitReaction(ImpactPoint);
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitEnemy();
}
void AEnemyCharacter::InitEnemy()
{
	AIController = Cast<AAIController>(GetController());
	CurrentPatrolTarget = TakeTargetForPatrolling();
	MoveToTarget(CurrentPatrolTarget);
}

void AEnemyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (HasReachAcceptableRadiusOfTarget(CurrentPatrolTarget, PatrolDistanceRadiusFromTheTargetPoint) && IsPatrolling())
	{
		EnemyActionState = EEAS_WaitForNextPatrolTarget;
		StartPatrolling();
		GEngine->AddOnScreenDebugMessage(1, 2.5f, FColor::Black, "Start Patrol Timer");
	}
}

bool AEnemyCharacter::HasReachAcceptableRadiusOfTarget(const AActor* Target, const double TargetRadius) const
{
	if (Target == nullptr) return false;
	const double DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Size();
	
	return TargetRadius >= DistanceToTarget;
}

void AEnemyCharacter::MoveToTarget(const AActor* Target) const
{
	if (AIController == nullptr || Target == nullptr) return;
	
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	MoveRequest.SetAcceptanceRadius(AcceptanceRadiusForReachTarget);
	AIController->MoveTo(MoveRequest);
}

bool AEnemyCharacter::IsPatrolling() const
{
	return EnemyActionState == EEAS_Patrolling;
}


void AEnemyCharacter::StartPatrolling()
{
	CurrentPatrolTarget = TakeTargetForPatrolling();
	const float PatrolTime = FMath::RandRange(MinWaitPatrolTime, MaxWaitPatrolTime);
	GetWorldTimerManager().SetTimer(PatrolTimer, this, &AEnemyCharacter::StartPatrolTimer, PatrolTime);
}

void AEnemyCharacter::StartPatrolTimer()
{
	MoveToTarget(CurrentPatrolTarget);
	EnemyActionState = EEAS_Patrolling;
}

void AEnemyCharacter::ClearPatrolTimer()
{
	GetWorldTimerManager().ClearTimer(PatrolTimer);
}

AActor* AEnemyCharacter::TakeTargetForPatrolling()
{
	if (VisitedPatrolTargets.Num() == PatrolTargets.Num())
	{
		VisitedPatrolTargets.Empty();
	}
	TArray<AActor*> ValidTargets;
	for (AActor* Target : PatrolTargets)
	{
		if (Target != CurrentPatrolTarget && !VisitedPatrolTargets.Contains(Target))
		{
			ValidTargets.AddUnique(Target);
		}
	}
	
	const int32 MaxSectionIndex = ValidTargets.Num() - 1;
	const int32 Selection = FMath::RandRange(0, MaxSectionIndex);
	VisitedPatrolTargets.AddUnique(ValidTargets[Selection]);
	return ValidTargets[Selection];
}

