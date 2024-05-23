// Copyright Dawid Harendarz.

#pragma once

#include "CoreMinimal.h"
#include "Interface/CombatInterface.h"
#include "Interface/ItemInterface.h"
#include "Item/ItemBase.h"
#include "Weapon.generated.h"

class UAnimMontage;
class UBoxComponent;
/**
 * 
 */
UCLASS()
class QUICKADVENTURE_API AWeapon : public AItemBase, public IItemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	//TODO: Move it to the BP
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	TObjectPtr<UBoxComponent> WeaponBox;

	UPROPERTY()
	TArray<AActor*> IgnoreActors;
	
	AWeapon();
	virtual void HandleInteractionKey(ALinariCharacter* Character) override;
	void AttachToSocketComponent(USceneComponent* Parent, FName const SocketName);

	UFUNCTION(BlueprintImplementableEvent)
	void DisableShapeCollisionForOverlap();
	
	FORCEINLINE FName GetDisarmSocket() const { return DisarmSocketName; }
	FORCEINLINE FName GetDisarmMontageSection() const {return DisarmMontageSection;}
	FORCEINLINE FName GetEquipMontageSection() const {return EquipMontageSection;}
	FORCEINLINE TObjectPtr<UAnimMontage> GetCombatMontage () const { return CombatMontage; };
	FORCEINLINE TArray<FName> GetCombatMontageSections () const { return CombatMontageSections; };
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent)
	void CreateFields(const FVector& FieldLocation);
private:


	//TODO: Move it to the BP
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	TObjectPtr<USceneComponent>BoxTraceStart;

	//TODO: Move it to the BP
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	TObjectPtr<USceneComponent>BoxTraceEnd;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	bool bUseDebug = false;

	//TODO: Move it to the BP
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	FVector BoxTraceSingleDistanceFromCenter = FVector(5.f);
	
	UPROPERTY(EditAnywhere, Category = "Animation Montages")
	TObjectPtr<UAnimMontage> CombatMontage;

	UPROPERTY(EditAnywhere, Category = "Animation Montages")
	TArray<FName> CombatMontageSections;

	UPROPERTY(EditAnywhere, Category = "Animation Montages")
	FName EquipMontageSection = "Default";

	UPROPERTY(EditAnywhere, Category = "Animation Montages")
	FName DisarmMontageSection = "Default";

	UPROPERTY(EditAnywhere, Category = "Animation Montages")
	FName DisarmSocketName = "Socket";

	void BoxTraceSingle(FHitResult& BoxHit);
};
