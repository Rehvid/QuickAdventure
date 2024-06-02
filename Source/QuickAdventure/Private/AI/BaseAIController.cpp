// Copyright Dawid Harendarz.
#include "AI/BaseAIController.h"

#include "Perception/AIPerceptionTypes.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISense_Sight.h"

void ABaseAIController::OnTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	checkf(BehaviorTree, TEXT("Behavior Tree is not initialzied, please fill out BP_BaseAiController"));
	checkf(BehaviorTree->GetBlackboardAsset(),TEXT("Blackboard Asset is not initialzied, please fill out your Behavior Tree"));
	
	const TSubclassOf<UAISense> AISenses = UAIPerceptionSystem::GetSenseClassForStimulus(this, Stimulus);
	if (IsNotPlayerStimulus(Actor) && IsAISenseStimulusAndBlackboardComponentIsValid(AISenses)) return;
	
	if (AISenses->IsChildOf(UAISense_Sight::StaticClass()))
	{
		OnHandleSightSense(Actor,  Stimulus);	
	}
}

void ABaseAIController::OnHandleSightSense(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		GetBlackboardComponent()->SetValueAsObject(FName(TEXT("TargetActor")), Actor);
	}
	else
	{
		GetBlackboardComponent()->SetValueAsObject(FName(TEXT("TargetActor")), nullptr);
		GetBlackboardComponent()->SetValueAsVector(FName(TEXT("LastKnownLocation")), Stimulus.StimulusLocation);
		GetBlackboardComponent()->SetValueAsFloat(FName(TEXT("AcceptanceRadius")), 100.f);
	}
}

bool ABaseAIController::IsAISenseStimulusAndBlackboardComponentIsValid(const TSubclassOf<UAISense> AISenses) const
{
	return AISenses != nullptr && GetBlackboardComponent() != nullptr;
}

bool ABaseAIController::IsNotPlayerStimulus(AActor* Actor) const
{
	const AActor* PlayerCharacter = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	return PlayerCharacter != Actor;
}
