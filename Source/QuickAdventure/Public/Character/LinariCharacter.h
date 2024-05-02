// Copyright Dawid Harendarz.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Interface/ItemInterface.h"
#include "LinariCharacter.generated.h"

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
	virtual void SetOverlappingItem(AItemBase* Item) override;
	UFUNCTION(BlueprintCallable)
	virtual void SetCharacterActionState(const ECharacterActionState NewCharacterActionState);
	virtual void SetCharacterState(const ECharacterState NewCharacterState);

	FORCEINLINE void SetCanJumpAgain(const bool CanJumpAgain) { bCanJumpAgain = CanJumpAgain;}
	FORCEINLINE bool CanJumpAgain() const { return bCanJumpAgain; }
	
	void InteractionKeyPressed();
	void EquipWeapon(AWeapon* Weapon);
	void HandleWeaponInteraction();
	bool CanPickUpWeapon() const;
	
	void Dodge();
	void PlayAttackSection();
	bool IsUnequipped() const;
	bool IsUnoccupied() const;
	bool CanJump() const;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECharacterState CharacterState = ECharacterState::ELCS_Unequipped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECharacterActionState CharacterAction = ECharacterActionState::ECAS_Unoccupied;

	virtual bool CanAttack() override;

	UFUNCTION(BlueprintCallable)
	virtual void AttachWeaponToHandSocket();

	UFUNCTION(BlueprintCallable)
	virtual void AttachWeaponToHoldSocket();
private:
	UPROPERTY(VisibleInstanceOnly, Category = "Actions")
	TObjectPtr<AItemBase> OverlappingItem;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<AWeapon> EquippedWeapon;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation Montages")
	TObjectPtr<UAnimMontage> DodgeAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animation Montages")
	TObjectPtr<UAnimMontage> EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animation Montages")
	TObjectPtr<UAnimMontage> DisarmMontage;

	UPROPERTY(VisibleAnywhere, Category = "Movement Properties")
	bool bCanJumpAgain = true;
	
	void PlayDodgeMontage();
	void PlayEquipMontage();
	void PlayDisarmMontage();
	bool CanEquipWeapon() const;
	bool CanDisarmWeapon() const;
};
