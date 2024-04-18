// Copyright Dawid Harendarz.

#include "Item/ItemBase.h"
#include "Interface/ItemInterface.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")));
}

float AItemBase::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

void AItemBase::OnOverlap(AActor* TargetActor)
{
	if (IItemInterface* ItemInterface = Cast<IItemInterface>(TargetActor))
	{
		ItemInterface->SetOverlappingItem(this);
	}
}

void AItemBase::OnEndOverlap(AActor* TargetActor)
{
	if (IItemInterface* ItemInterface = Cast<IItemInterface>(TargetActor))
	{
		ItemInterface->SetOverlappingItem(nullptr);
	}
}

void AItemBase::InitializeCollisionForMesh(UStaticMeshComponent* MeshComponent)
{
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
