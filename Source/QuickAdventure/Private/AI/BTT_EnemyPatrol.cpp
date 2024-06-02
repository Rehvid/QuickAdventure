// Copyright Dawid Harendarz.


#include "AI/BTT_EnemyPatrol.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/BaseEnemy.h"

EBTNodeResult::Type UBTT_EnemyPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	CachedOwnerComp = &OwnerComp;

	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	if (AIController && BlackboardComponent)
	{
		MoveTo(AIController, BlackboardComponent);
	}
	
	return EBTNodeResult::InProgress;
}


void UBTT_EnemyPatrol::MoveTo(AAIController* AIController, UBlackboardComponent* BlackboardComponent)
{
	LastKnownLocation = BlackboardComponent->GetValueAsVector(TEXT("LastKnownLocation"));
	AIController->ReceiveMoveCompleted.AddDynamic(this, &UBTT_EnemyPatrol::MoveCompleted);
	const float AcceptanceRadius = BlackboardComponent->GetValueAsFloat(TEXT("AcceptanceRadius"));
	
	if (LastKnownLocation.IsZero())
	{
		if (AActor* PatrolTarget = Cast<AActor>(BlackboardComponent->GetValueAsObject(TEXT("PatrolTarget"))))
		{
			AIController->MoveToActor(PatrolTarget, AcceptanceRadius);
		}
	}
	else
	{
		AIController->MoveToLocation(LastKnownLocation, AcceptanceRadius);
	}
}

void UBTT_EnemyPatrol::MoveCompleted(FAIRequestID RequestID,  EPathFollowingResult::Type Result)
{
	UBlackboardComponent* BlackboardComponent = CachedOwnerComp->GetBlackboardComponent();
	AAIController* AIController = CachedOwnerComp->GetAIOwner();

	if (BlackboardComponent && AIController)
	{
		if (!LastKnownLocation.IsZero())
        {
        	BlackboardComponent->SetValueAsVector(FName(TEXT("LastKnownLocation")), FVector::Zero());
        }
		
		AIController->ReceiveMoveCompleted.RemoveDynamic(this, &UBTT_EnemyPatrol::MoveCompleted);
	
		FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Succeeded);
	};
	
	FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Failed);
}
