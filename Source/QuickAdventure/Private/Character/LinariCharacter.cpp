// Copyright Dawid Harendarz.

#include "Character/LinariCharacter.h"

#include "Item/ItemBase.h"
#include "Item/Weapon/Weapon.h"

void ALinariCharacter::SetOverlappingItem(AItemBase* Item)
{
	OverlappingItem = Item;
}

void ALinariCharacter::SetCharacterActionState(const ECharacterActionState NewCharacterActionState)
{
	CharacterAction = NewCharacterActionState;
}

void ALinariCharacter::SetCharacterState(const ECharacterState NewCharacterState)
{
	CharacterState = NewCharacterState;
}

void ALinariCharacter::InteractionKeyPressed()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->HandleInteractionKey(this);
	}
	
	if (IItemInterface* ItemInterface = Cast<IItemInterface>(OverlappingItem))
	{
		ItemInterface->HandleInteractionKey(this);
	}
}

void ALinariCharacter::EquipWeapon(AWeapon* Weapon)
{
	EquippedWeapon = Weapon;
	SetCharacterState(ECharacterState::ELCS_EquippedWeapon);
	SetOverlappingItem(nullptr);
}

void ALinariCharacter::HandleWeaponInteraction()
{
	if (CanDisarmWeapon())
	{
		PlayDisarmMontage();
	} else if (CanEquipWeapon())
	{
		PlayEquipMontage();
	}
}

bool ALinariCharacter::CanPickUpWeapon() const
{
	return CharacterAction == ECharacterActionState::ECAS_Unoccupied
		&& CharacterState == ECharacterState::ELCS_Unequipped
		&& !EquippedWeapon;
}

void ALinariCharacter::Dodge()
{
	if (CharacterAction == ECharacterActionState::ECAS_Unoccupied)
	{
		PlayDodgeMontage();
		SetCharacterActionState(ECharacterActionState::ECAS_Dodging);
	}
}

void ALinariCharacter::PlayAttackSection()
{
	if (EquippedWeapon && CanAttack())
	{
		PlayCombatSection(EquippedWeapon->GetCombatMontage(), EquippedWeapon->GetCombatMontageSections());
		SetCharacterActionState(ECharacterActionState::ECAS_Attacking);
	}
}

bool ALinariCharacter::IsUnequipped() const
{
	return CharacterState == ECharacterState::ELCS_Unequipped;
}

bool ALinariCharacter::IsUnoccupied() const
{
	return CharacterAction == ECharacterActionState::ECAS_Unoccupied;
}


bool ALinariCharacter::CanAttack()
{
	return CharacterAction == ECharacterActionState::ECAS_Unoccupied
		&& CharacterState != ECharacterState::ELCS_Unequipped;
}

void ALinariCharacter::AttachWeaponToHandSocket()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachToSocketComponent(GetMesh(), RightHandSocketName);
		SetCharacterActionState(ECharacterActionState::ECAS_Unoccupied);
	}
}

void ALinariCharacter::AttachWeaponToHoldSocket()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachToSocketComponent(GetMesh(), EquippedWeapon->GetDisarmSocket());
		SetCharacterActionState(ECharacterActionState::ECAS_Unoccupied);
	}
}

void ALinariCharacter::PlayDodgeMontage()
{
	if (DodgeAnimMontage)
	{
		PlayMontageSection(DodgeAnimMontage, DefaultSection);
	}
}

void ALinariCharacter::PlayEquipMontage()
{
	PlayMontageSection(EquipMontage, EquippedWeapon->GetEquipMontageSection());
	SetCharacterActionState(ECharacterActionState::ECAS_EquippingWeapon);
	SetCharacterState(ECharacterState::ELCS_EquippedWeapon);
}

void ALinariCharacter::PlayDisarmMontage()
{
	PlayMontageSection(DisarmMontage, EquippedWeapon->GetDisarmMontageSection());
	SetCharacterActionState(ECharacterActionState::ECAS_EquippingWeapon);
	SetCharacterState(ECharacterState::ELCS_Unequipped);
}

bool ALinariCharacter::CanEquipWeapon() const
{
	return CharacterAction == ECharacterActionState::ECAS_Unoccupied
		&& IsUnequipped()
		&& EquippedWeapon;
}

bool ALinariCharacter::CanDisarmWeapon() const
{
	return CharacterAction == ECharacterActionState::ECAS_Unoccupied
		&& !IsUnequipped();
}


