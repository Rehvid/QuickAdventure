// Copyright Dawid Harendarz.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "BaseEnemy.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPatrolPoint
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> PatrolPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinWaitTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxWaitTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AcceptanceRadius = 50.f;
};

UCLASS()
class QUICKADVENTURE_API ABaseEnemy : public ACharacterBase
{
	GENERATED_BODY()

public:
	ABaseEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPatrolPoint> PatrolPath;

	UPROPERTY(VisibleAnywhere)
	int32 CurrentPatrolPointIndex;

	UFUNCTION(BlueprintCallable)
	FPatrolPoint TakeRandomPatrolPoint();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetCurrentPatrolPointIndex(const int32 PatrolPointIndex) {CurrentPatrolPointIndex = PatrolPointIndex;}
};