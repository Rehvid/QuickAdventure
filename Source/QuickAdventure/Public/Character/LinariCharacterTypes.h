#pragma once

UENUM(BlueprintType)
enum class ELinariCharacterState : uint8
{
	ELCS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	ELCS_Walking UMETA(DisplayName = "Walking"),
	ELCS_Running UMETA(DisplayName = "Running"),
	ELCS_Crouch UMETA(DisplayName = "Crouching"),
	ELCS_Jumping UMETA(DisplayName = "Jumping"),
	ELCS_EquippedWeapon UMETA(DisplayName = "Equipped Weapon")
};