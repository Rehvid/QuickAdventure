// Copyright Dawid Harendarz.

#include "Item/Weapon/Weapon.h"
#include "Character/LinariCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AWeapon::AWeapon()
{
	WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponBox"));
	WeaponBox->SetupAttachment(GetRootComponent());

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("BoxTraceStart"));
	BoxTraceStart->SetupAttachment(GetRootComponent());

	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("BoxTraceEnd"));
	BoxTraceEnd->SetupAttachment(GetRootComponent());
}

void AWeapon::HandleInteractionKey(ALinariCharacter* Character)
{
	if (Character->CanPickUpWeapon())
	{
		AttachToSocketComponent(Character->GetMesh(), Character->GetRightHandSocketName());
		Character->EquipWeapon(this);
	}
	else
	{
		Character->HandleWeaponInteraction();
	}
}

void AWeapon::AttachToSocketComponent(USceneComponent* Parent, FName const SocketName)
{
	FAttachmentTransformRules const TransformRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Parent, TransformRules, SocketName);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxOverlap);
}

void AWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                           int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	ActorsToIgnore.Add(GetOwner());

	if (ICombatInterface *CombatInterface = Cast<ICombatInterface>(OtherActor))
	{
		CombatInterface->GetHit();
	}

	
	FHitResult BoxHit = SweepResult;
	const FVector Start = BoxTraceStart->GetComponentLocation();
	const FVector End = BoxTraceEnd->GetComponentLocation();
	
	UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		FVector(1.f),
		BoxTraceStart->GetComponentRotation(),
		TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		BoxHit,
		true
	);

	CreateFields(BoxHit.ImpactPoint);
	//TODO: ApplyDamage by GameplayEffects
}



