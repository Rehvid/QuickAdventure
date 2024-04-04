// Copyright Dawid Harendarz.


#include "..\..\Public\Character\CharacterBase.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}


