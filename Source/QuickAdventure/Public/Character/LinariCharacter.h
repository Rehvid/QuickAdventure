// Copyright Dawid Harendarz.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interface/ItemInterface.h"
#include "LinariCharacter.generated.h"

class UPlayerAnimationsDataConfig;
class UPlayerInputDataConfig;
class AWeapon;
class AItemBase;
class UInputComponent;
class UInputMappingContext;
class UInputAction;
class UAnimMontage;

struct FInputActionValue;

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ELCS_Unequipped UMETA(DisplayName = "Unequipped"),
	ELCS_EquippedWeapon UMETA(DisplayName = "Equipped Weapon")
};

UENUM(BlueprintType)
enum class ECharacterActionState: uint8
{
	ECAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	ECAS_Attacking UMETA(DisplayName = "Attacking"),
	ECAS_Jumping UMETA(DisplayName = "Jumping"),
	ECAS_Dodging UMETA(DisplayName = "Dodging"),
	ECAS_Crouching UMETA(DisplayName = "Crouching"),
	ECAS_EquippingWeapon UMETA(DisplayName ="Equipping Weapon")
};

/**
 * 
 */
UCLASS()
class QUICKADVENTURE_API ALinariCharacter : public ACharacterBase, public IItemInterface
{
	GENERATED_BODY()

public:
	FORCEINLINE virtual void SetOverlappingItem(AItemBase* Item) override { OverlappingItem = Item; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetCharacterActionState(const ECharacterActionState NewCharacterActionState) { CharacterActionState = NewCharacterActionState; }
	FORCEINLINE void SetCharacterState(const ECharacterState NewCharacterState) { CharacterState = NewCharacterState; }
	FORCEINLINE void SetCharacterMovementMaxSpeedWalk(const double Speed) const { GetCharacterMovement()->MaxWalkSpeed = Speed;}
	
	void EquipWeapon(AWeapon* Weapon);
	void HandleWeaponInteraction();
	bool CanPickUpWeapon() const;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
	ECharacterState CharacterState = ECharacterState::ELCS_Unequipped;
          
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
	ECharacterActionState CharacterActionState = ECharacterActionState::ECAS_Unoccupied;

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual bool CanAttack() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void AttachWeaponToHandSocket();
	UFUNCTION(BlueprintCallable)
	virtual void AttachWeaponToHoldSocket();
private:
	UPROPERTY(VisibleAnywhere, Category = "Items")
	TObjectPtr<AItemBase> OverlappingItem;

	UPROPERTY(VisibleAnywhere, Category = "Items")
	TObjectPtr<AWeapon> EquippedWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	TObjectPtr<UInputMappingContext> PlayerContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	UPlayerInputDataConfig* PlayerInputActions;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UPlayerAnimationsDataConfig* PlayerAnimations;
	
	UPROPERTY(VisibleAnywhere, Category = "Movement Properties")
	bool bIsJumpAvailable = true;

	UPROPERTY(EditAnywhere, Category = "Movement Properties")
	double WaitTimeUntilJumpAgain = 1.f;

	FTimerHandle CountdownTimerToJumpAgain;

	UPROPERTY(EditAnywhere, Category = "Movement Properties")
	double WalkSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = "Movement Properties")
	double RunSpeed = 600.f;
	
	void Move(const FInputActionValue& InputActionValue);
	void StartRunning();
	void StopRunning();
	void Look(const FInputActionValue& InputActionValue);
	virtual void Jump() override;
	void StartCountdownTimerToJumpAgain();
	void ClearCountdownTimerToJumpAgain();
	void StartCrouching();
	void StopCrouching();
	void Dodge();
	void HandleInteractionKeyPressed();
	void PlayDodgeMontage();
	void Attack();
	void PlayAttackSection();
	bool CanEquipWeapon() const;
	void PlayEquipMontage();
	bool CanDisarmWeapon() const;
	void PlayDisarmMontage();
	bool IsUnequipped() const;
	bool IsUnoccupied() const;
	bool IsJumpAvailable() const;
};