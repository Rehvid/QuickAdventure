// Copyright Dawid Harendarz.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_EnemyPatrol.generated.h"

namespace EPathFollowingResult
{
	enum Type : int;
}

struct FPathFollowingResult;
/**
 * 
 */
UCLASS()
class QUICKADVENTURE_API UBTT_EnemyPatrol : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY()
	UBehaviorTreeComponent* CachedOwnerComp;

	FVector LastKnownLocation;

	UFUNCTION()
	void MoveTo(AAIController* AIController, UBlackboardComponent* BlackboardComponent);
	
	UFUNCTION()
	void MoveCompleted(FAIRequestID RequestID,  EPathFollowingResult::Type Result);
};
