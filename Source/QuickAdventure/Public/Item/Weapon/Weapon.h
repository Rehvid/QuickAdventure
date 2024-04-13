// Copyright Dawid Harendarz.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemBase.h"
#include "Weapon.generated.h"

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
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	TObjectPtr<UBoxComponent> WeaponBox;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	TObjectPtr<USceneComponent>BoxTraceStart;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	TObjectPtr<USceneComponent>BoxTraceEnd;	
};
