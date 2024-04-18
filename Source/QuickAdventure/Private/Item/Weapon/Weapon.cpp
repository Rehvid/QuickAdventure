// Copyright Dawid Harendarz.


#include "Item/Weapon/Weapon.h"

#include "Components/BoxComponent.h"

AWeapon::AWeapon()
{
	WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponBox"));
	WeaponBox->SetupAttachment(GetRootComponent());

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("BoxTraceStart"));
	BoxTraceStart->SetupAttachment(GetRootComponent());

	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("BoxTraceEnd"));
	BoxTraceEnd->SetupAttachment(GetRootComponent());
}

void AWeapon::Equip(USceneComponent* Parent, FName const SocketName)
{
	FAttachmentTransformRules const TransformRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Parent, TransformRules, SocketName);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxOverlap);
}

void AWeapon::OnOverlap(AActor* TargetActor)
{
	Super::OnOverlap(TargetActor);
	
	UE_LOG(LogTemp, Warning, TEXT("Start Overlapping"));
}

void AWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                           int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Start BoxOverlapping"));
}
