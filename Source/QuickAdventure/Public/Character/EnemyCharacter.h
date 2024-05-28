// Copyright Dawid Harendarz.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "EnemyCharacter.generated.h"

class AAIController;
/**
 * 
 */


UENUM()
enum EEnemyActionState
{
	EEAS_Patrolling,
	EEAS_WaitForNextPatrolTarget
};

UCLASS()
class QUICKADVENTURE_API AEnemyCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	virtual void GetHit(const FVector& ImpactPoint) override;
	
	UPROPERTY()
	TObjectPtr<AAIController> AIController;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Navigation")
	AActor* CurrentPatrolTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Navigation")
	double PatrolDistanceRadiusFromTheTargetPoint = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Navigation")
	float AcceptanceRadiusForReachTarget = 50.f;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


private:
	EEnemyActionState EnemyActionState = EEAS_Patrolling;
	
	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> VisitedPatrolTargets;

	bool HasReachAcceptableRadiusOfTarget(const AActor* Target, const double TargetRadius) const;
	bool bIsTrackingTargetReach = false;

	FTimerHandle PatrolTimer;

	UPROPERTY(VisibleAnywhere)
	float MinWaitPatrolTime = 1.f;

	UPROPERTY(VisibleAnywhere)
	float MaxWaitPatrolTime = 5.f;

	void InitEnemy();
	void StartPatrolling();
	AActor* TakeTargetForPatrolling();
	void StartPatrolTimer();
	void ClearPatrolTimer();
	void MoveToTarget(const AActor* Target) const;

	bool IsPatrolling() const;
};
