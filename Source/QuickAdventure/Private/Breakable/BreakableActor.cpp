// Copyright Dawid Harendarz.

#include "Breakable/BreakableActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Components/CapsuleComponent.h"

ABreakableActor::ABreakableActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("Geometry Mesh"));
	GeometryCollection->SetGenerateOverlapEvents(true);
	SetRootComponent(GeometryCollection);
	
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(GetRootComponent());
}

void ABreakableActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABreakableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABreakableActor::GetHit(const FVector& ImpactPoint)
{
	Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	SetLifeSpan(LifeSpanTime);
}

