// Copyright Dawid Harendarz.

#include "Character/LinariCharacter.h"

#include "Item/ItemBase.h"
#include "Item/Weapon/Weapon.h"

void ALinariCharacter::SetOverlappingItem(AItemBase* Item)
{
	OverlappingItem = Item;
}

void ALinariCharacter::Dodge()
{
	if (CharacterAction == ECharacterActionState::ECAS_Unoccupied)
	{
		PlayDodgeMontage();
		CharacterAction = ECharacterActionState::ECAS_Dodging;
	}
}

void ALinariCharacter::EKeyPressed()
{
	if (AWeapon* Weapon = Cast<AWeapon>(OverlappingItem))
	{
		EquipWeapon(Weapon);
	}
}

void ALinariCharacter::PlayAttackSection()
{
	if (EquippedWeapon && CanAttack())
	{
		PlayCombatSection(EquippedWeapon->GetCombatMontage(), EquippedWeapon->GetCombatMontageSections());
		CharacterAction = ECharacterActionState::ECAS_Attacking;
	}
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

void ALinariCharacter::AttackEnd()
{
	CharacterAction = ECharacterActionState::ECAS_Unoccupied;
}

void ALinariCharacter::DodgeEnd()
{
	CharacterAction = ECharacterActionState::ECAS_Unoccupied;
}

void ALinariCharacter::EquipWeapon(AWeapon* Weapon)
{
	Weapon->Equip(GetMesh(), RightHandSocketName);
	EquippedWeapon = Weapon;
	CharacterState = ECharacterState::ELCS_EquippedWeapon;
	OverlappingItem = nullptr;
}

void ALinariCharacter::PlayDodgeMontage()
{
	if (DodgeAnimMontage)
	{
		PlayMontageSection(DodgeAnimMontage, DefaultSection);
	}
}



