// Copyright Dawid Harendarz.

#include "Item/ItemBase.h"

#include "Components/SphereComponent.h"
#include "Interface/ItemInterface.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(ItemMesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AItemBase::OnSphereEndOverlap);
}

float AItemBase::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

void AItemBase::OnSphereOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
) {
	if (IItemInterface* ItemInterface = Cast<IItemInterface>(OtherActor))
	{
		ItemInterface->SetOverlappingItem(this);
	}
}

void AItemBase::OnSphereEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex
) {
	if (IItemInterface* ItemInterface = Cast<IItemInterface>(OtherActor))
	{
		ItemInterface->SetOverlappingItem(nullptr);
	}
}

