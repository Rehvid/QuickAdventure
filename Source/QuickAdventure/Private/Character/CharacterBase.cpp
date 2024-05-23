// Copyright Dawid Harendarz.

#include "..\..\Public\Character\CharacterBase.h"
#include "Animation/AnimMontage.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterBase::PlayMontageSection(UAnimMontage* Montage, const FName& SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	
	if (Montage && AnimInstance)
	{
		AnimInstance->Montage_Play(Montage);
		AnimInstance->Montage_JumpToSection(SectionName, Montage);
	}	
}

bool ACharacterBase::CanAttack()
{
	return false;
}

void ACharacterBase::PlayCombatSection(UAnimMontage* CombatMontage, const TArray<FName> CombatMontageSections)
{
	if (CombatMontage)
	{
		PlayRandomMontageSection(CombatMontage, CombatMontageSections);
	}
}

void ACharacterBase::PlayRandomMontageSection(UAnimMontage* Montage, const TArray<FName>& Sections)
{
	if (Sections.Num() <= 0) return;

	const int32 MaxSectionIndex = Sections.Num() - 1;
	const int32 Selection = FMath::RandRange(0, MaxSectionIndex);
	const FName SectionToPlay = Sections[Selection];
	
	PlayMontageSection(Montage, SectionToPlay);
}

void ACharacterBase::HitReaction(const FVector& ImpactPoint)
{
	const FVector Forward = GetActorForwardVector();
	const FVector ImpactLowered(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);
	const FVector ToHit = (ImpactLowered - GetActorLocation()).GetSafeNormal();
	const double CosTheta = FVector::DotProduct(Forward, ToHit);
	double Theta = FMath::Acos(CosTheta);
	Theta = FMath::RadiansToDegrees(Theta);
	const FVector CrossProduct = FVector::CrossProduct(Forward, ToHit);
	if (CrossProduct.Z < 0)
	{
		Theta *= -1.f;
	}

	FName Section("FromBack");
	if (Theta >= -45.f && Theta < 45.f)
	{
		Section = FName("FromFront");
	}
	else if (Theta >= -135.f && Theta < -45.f)
	{
		Section = FName("FromLeft");
	}
	else if (Theta >= 45.f && Theta < 135.f)
	{
		Section = FName("FromRight");
	}

	PlayMontageSection(HitReactionMontage, Section);
}
