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

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ELCS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	ELCS_EquippedWeapon UMETA(DisplayName = "Equipped Weapon")
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
	bool IsUnoccupied() const;
private:
	/* Character States */
	UPROPERTY(VisibleAnywhere)
	ECharacterState CharacterState = ECharacterState::ELCS_Unoccupied;
	
	UPROPERTY(VisibleInstanceOnly, Category = "Actions")
	TObjectPtr<AItemBase> OverlappingItem;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<AWeapon> EquippedWeapon;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation Montages")
	TObjectPtr<UAnimMontage> DodgeAnimMontage;
	
	void PlayDodgeMontage();
	void EquipWeapon(AWeapon* Weapon);
};
