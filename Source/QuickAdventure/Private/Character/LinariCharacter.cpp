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
	PlayDodgeMontage();
}

void ALinariCharacter::EKeyPressed()
{
	if (AWeapon* Weapon = Cast<AWeapon>(OverlappingItem))
	{
		EquipWeapon(Weapon);
	}
}

void ALinariCharacter::EquipWeapon(AWeapon* Weapon)
{
	Weapon->Equip(GetMesh());
	EquippedWeapon = Weapon;
	OverlappingItem = nullptr;
}

void ALinariCharacter::PlayDodgeMontage()
{
	if (DodgeAnimMontage)
	{
		PlayMontageSection(DodgeAnimMontage, FName("Default"));
	}
}

bool ALinariCharacter::IsUnoccupied() const
{
	return CharacterState == ELinariCharacterState::ELCS_Unoccupied;
}

bool ALinariCharacter::IsRunning() const
{
	return CharacterState == ELinariCharacterState::ELCS_Running;
}

bool ALinariCharacter::IsWalking() const
{
	return CharacterState == ELinariCharacterState::ELCS_Walking;
}
