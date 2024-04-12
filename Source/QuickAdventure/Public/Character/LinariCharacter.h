// Copyright Dawid Harendarz.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "LinariCharacterTypes.h"
#include "Interface/ItemInterface.h"
#include "LinariCharacter.generated.h"

class AWeapon;
class AItemBase;
class UInputComponent;
class UInputMappingContext;
class UInputAction;
class UAnimMontage;

struct FInputActionValue;

/**
 * 
 */
UCLASS()
class QUICKADVENTURE_API ALinariCharacter : public ACharacterBase, public IItemInterface
{
	GENERATED_BODY()

public:
	virtual void SetOverlappingItem(AItemBase* Item) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
private:
	/* Enhanced Input Functions */
	void InitializeMappingContext();
	void InitializeEnhancedInputActions(UInputComponent* PlayerInputComponent);
	void Move(const FInputActionValue& InputActionValue);
	void StartRunning();
	void StopRunning(); 
	void Look(const FInputActionValue& InputActionValue);
	void Jump(const FInputActionValue& InputActionValue);
	void Crouch(const FInputActionValue& InputActionValue);
	void UnCrouch();
	void Dodge();
	void EKeyPressed(const FInputActionValue& InputActionValue);
	void EquipWeapon(AWeapon* Weapon);
	
	/* Animations Montages Functions */
	void PlayDodgeMontage();

	bool IsUnoccupied() const;
	bool IsRunning() const;
	bool IsWalking() const;
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ELinariCharacterState CharacterState = ELinariCharacterState::ELCS_Unoccupied;

	UPROPERTY(VisibleInstanceOnly, Category = "Actions")
	TObjectPtr<AItemBase> OverlappingItem;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<AWeapon> EquippedWeapon;
	
	/* Enhanced Input Properties */
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	TObjectPtr<UInputMappingContext> MappingContext;
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Movement")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Movement")
	TObjectPtr<UInputAction> RunAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Movement")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Movement")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Movement")
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Action")
	TObjectPtr<UInputAction> EKeyPressedAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Combat")
	TObjectPtr<UInputAction> DodgeAction;

	/* Animations Montages Properties */
	UPROPERTY(EditDefaultsOnly, Category = "Animation Montages | Combat")
	TObjectPtr<UAnimMontage> DodgeAnimMontage;

	UPROPERTY(EditAnywhere, Category = "Movement")
	double WalkingSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	double RunningSpeed = 600.f;
};
