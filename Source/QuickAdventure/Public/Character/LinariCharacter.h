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
	ECAS_Dodging UMETA(DisplayName = "Dodging")
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
	
	void Dodge();
	void EKeyPressed();
	void PlayAttackSection();
	bool IsUnoccupied() const;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECharacterState CharacterState = ECharacterState::ELCS_Unequipped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECharacterActionState CharacterAction = ECharacterActionState::ECAS_Unoccupied;

	virtual bool CanAttack() override;
	virtual void AttackEnd() override;

	UFUNCTION(BlueprintCallable)
	virtual void DodgeEnd();
private:
	UPROPERTY(VisibleInstanceOnly, Category = "Actions")
	TObjectPtr<AItemBase> OverlappingItem;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<AWeapon> EquippedWeapon;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation Montages")
	TObjectPtr<UAnimMontage> DodgeAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animation Montages")
	TObjectPtr<UAnimMontage> EquipMontage;
	
	void PlayDodgeMontage();
	void EquipWeapon(AWeapon* Weapon);
	void PlayEquipMontage();
	bool CanEquipWeapon() const;
};
