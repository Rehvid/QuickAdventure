// Copyright Dawid Harendarz.


#include "Item/Treasure.h"

ATreasure::ATreasure()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATreasure::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATreasure::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	RunningTime += DeltaSeconds;
	
	AddActorWorldOffset(FVector(0, 0, TransformedSin()));
}

void ATreasure::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Destroy();
}

