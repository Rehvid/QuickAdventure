// Copyright Dawid Harendarz.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS(Abstract)
class QUICKADVENTURE_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();
		
	virtual void PlayCombatSection(UAnimMontage* CombatMontage, const TArray<FName> CombatMontageSections);


	FORCEINLINE FName GetRightHandSocketName() const { return RightHandSocketName; } 
protected:
	UPROPERTY(EditAnywhere, Category = "Combat")
	FName RightHandSocketName;

	UPROPERTY(EditAnywhere, Category = "Animation Montages")
	FName DefaultSection;
	
	virtual void BeginPlay() override;
	virtual void PlayMontageSection(UAnimMontage* Montage, const FName& SectionName);
	virtual bool CanAttack();
	
	void PlayRandomMontageSection(UAnimMontage* Montage, const TArray<FName>& Sections);
};
