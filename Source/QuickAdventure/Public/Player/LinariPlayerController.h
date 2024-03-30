// Copyright Dawid Harendarz.

#pragma once
#include "InputActionValue.h"

class UInputMappingContext;
class UInputAction;

struct FInputActionValue;

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LinariPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class QUICKADVENTURE_API ALinariPlayerController : public APlayerController
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;
	
	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	void Jump(const FInputActionValue& InputActionValue);
};
