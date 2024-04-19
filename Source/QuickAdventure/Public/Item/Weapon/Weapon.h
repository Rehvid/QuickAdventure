// Copyright Dawid Harendarz.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemBase.h"
#include "Weapon.generated.h"

class UAnimMontage;
class UBoxComponent;
/**
 * 
 */
UCLASS()
class QUICKADVENTURE_API AWeapon : public AItemBase
{
	GENERATED_BODY()

public:
	AWeapon();
	void Equip(USceneComponent* Parent, FName const SocketName);

	FORCEINLINE FName GetEquipMontageSection() const {return EquipMontageSection;}
	FORCEINLINE TObjectPtr<UAnimMontage> GetCombatMontage () const { return CombatMontage; };
	FORCEINLINE TArray<FName> GetCombatMontageSections () const { return CombatMontageSections; };
protected:
	virtual void BeginPlay() override;

	virtual void OnOverlap(AActor* TargetActor) override;
	
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	TObjectPtr<UBoxComponent> WeaponBox;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	TObjectPtr<USceneComponent>BoxTraceStart;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	TObjectPtr<USceneComponent>BoxTraceEnd;
	
	UPROPERTY(EditAnywhere, Category = "Animation Montages")
	TObjectPtr<UAnimMontage> CombatMontage;

	UPROPERTY(EditAnywhere, Category = "Animation Montages")
	TArray<FName> CombatMontageSections;

	UPROPERTY(EditAnywhere, Category = "Animation Montages")
	FName EquipMontageSection = "Default";
};
