#pragma once

UENUM(BlueprintType)
enum class ELinariCharacterState : uint8
{
	ELCS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	ELCS_Walking UMETA(DisplayName = "Walking"),
	ELCS_Running UMETA(DisplayName = "Running")
};