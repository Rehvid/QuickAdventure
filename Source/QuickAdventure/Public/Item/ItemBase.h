// Copyright Dawid Harendarz.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

class USphereComponent;

UCLASS(Abstract)
class QUICKADVENTURE_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemBase();

protected:
	virtual float TransformedSin();

	UFUNCTION(BlueprintCallable)
	virtual void OnOverlap(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable)
	virtual void OnEndOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	virtual void InitializeCollisionForMesh(UStaticMeshComponent* MeshComponent);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float Amplitude = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float TimeConstant = 5.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sine Parameters")
	float RunningTime;
};
