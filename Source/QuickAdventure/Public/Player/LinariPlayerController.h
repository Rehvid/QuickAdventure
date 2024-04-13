// Copyright Dawid Harendarz.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LinariPlayerController.generated.h"

class ALinariCharacter;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

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
	UPROPERTY()
	TObjectPtr<ALinariCharacter> ControlledPawn;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> LinariContext;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> RunAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> DodgeAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> EKeyPressedAction;

	UPROPERTY(EditAnywhere, Category = "Movement Properties")
	double WalkingSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = "Movement Properties")
	double RunningSpeed = 600.f;

	void Move(const FInputActionValue& InputActionValue);
	void StartRunning();
	void StopRunning(); 
	void Look(const FInputActionValue& InputActionValue);
	void StartJump();
	void StartCrouching();
	void StopCrouching();
	void Dodge();
	void EKeyPressed();
};
