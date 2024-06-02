// Copyright Dawid Harendarz.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

class UAISense;
class UBehaviorTree;
struct FAIStimulus;
/**
 * 
 */
UCLASS()
class QUICKADVENTURE_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void OnTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Navigation")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	virtual void OnHandleSightSense(AActor* Actor, FAIStimulus Stimulus);
	
	virtual bool IsAISenseStimulusAndBlackboardComponentIsValid(const TSubclassOf<UAISense> AISenses) const;
	virtual bool IsNotPlayerStimulus(AActor* Actor) const;
};
