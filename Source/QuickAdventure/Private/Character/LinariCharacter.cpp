// Copyright Dawid Harendarz.

#include "Character/LinariCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAsset/PlayerAnimationsDataConfig.h"
#include "DataAsset/PlayerInputDataConfig.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Item/ItemBase.h"
#include "Item/Weapon/Weapon.h"

void ALinariCharacter::EquipWeapon(AWeapon* Weapon)
{
	EquippedWeapon = Weapon;
	SetCharacterState(ECharacterState::ELCS_EquippedWeapon);
	SetOverlappingItem(nullptr);
}

void ALinariCharacter::HandleWeaponInteraction()
{
	if (CanDisarmWeapon())
	{
		PlayDisarmMontage();
	} else if (CanEquipWeapon())
	{
		PlayEquipMontage();
	}
}

bool ALinariCharacter::CanPickUpWeapon() const
{
	return IsUnoccupied()
		&& IsUnequipped()
		&& !EquippedWeapon;
}

void ALinariCharacter::BeginPlay()
{
	Super::BeginPlay();

	checkf(PlayerContext, TEXT("Linari Context is not initialzied, please fill out BP_LinariCharacter"));
	checkf(PlayerInputActions, TEXT("Input actions are not initalized, please fill out DA_PlayerInputDataConfig"));

	const APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (!PlayerController) return;
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(PlayerContext, 0);
    }
	
}

void ALinariCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(PlayerInputActions->Move, ETriggerEvent::Triggered, this, &ALinariCharacter::Move);
	
		Input->BindAction(PlayerInputActions->Run, ETriggerEvent::Started, this, &ALinariCharacter::StartRunning);
		Input->BindAction(PlayerInputActions->Run, ETriggerEvent::Completed, this, &ALinariCharacter::StopRunning);

		Input->BindAction(PlayerInputActions->Look, ETriggerEvent::Triggered, this, &ALinariCharacter::Look);

		Input->BindAction(PlayerInputActions->Jump, ETriggerEvent::Triggered, this, &ALinariCharacter::Jump);

		Input->BindAction(PlayerInputActions->Crouch, ETriggerEvent::Started, this, &ALinariCharacter::StartCrouching);
		Input->BindAction(PlayerInputActions->Crouch, ETriggerEvent::Completed, this, &ALinariCharacter::StopCrouching);
		
		Input->BindAction(PlayerInputActions->Dodge, ETriggerEvent::Triggered, this, &ALinariCharacter::Dodge);

		Input->BindAction(PlayerInputActions->InteractionKey, ETriggerEvent::Triggered, this, &ALinariCharacter::HandleInteractionKeyPressed);
		
		Input->BindAction(PlayerInputActions->Attack, ETriggerEvent::Triggered, this, &ALinariCharacter::Attack);
	}
}

void ALinariCharacter::Move(const FInputActionValue& InputActionValue)
{
	if (!IsUnoccupied()) return;
	
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(ForwardDirection, InputAxisVector.Y);
	AddMovementInput(RightDirection, InputAxisVector.X);
}

void ALinariCharacter::StartRunning()
{
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		SetCharacterMovementMaxSpeedWalk(RunSpeed);
	}
}

void ALinariCharacter::StopRunning()
{
	SetCharacterMovementMaxSpeedWalk(WalkSpeed);
}

void ALinariCharacter::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookVector = InputActionValue.Get<FVector2D>();
	AddControllerPitchInput(LookVector.Y);
	AddControllerYawInput(LookVector.X);
}

void ALinariCharacter::Jump()
{
	if (IsJumpAvailable())
	{
		SetCharacterActionState(ECharacterActionState::ECAS_Jumping);
		Super::Jump();
		bIsJumpAvailable = false;
		StartCountdownTimerToJumpAgain();
	}
}

void ALinariCharacter::StartCountdownTimerToJumpAgain()
{
	GetWorldTimerManager().SetTimer(CountdownTimerToJumpAgain, this, &ALinariCharacter::ClearCountdownTimerToJumpAgain, WaitTimeUntilJumpAgain);
}

void ALinariCharacter::ClearCountdownTimerToJumpAgain()
{
	GetWorldTimerManager().ClearTimer(CountdownTimerToJumpAgain);
	bIsJumpAvailable = true;
}

void ALinariCharacter::StartCrouching()
{
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		SetCharacterActionState(ECharacterActionState::ECAS_Crouching);
		Crouch();
	}
}

void ALinariCharacter::StopCrouching()
{
	if (GetCharacterMovement()->IsCrouching())
	{
		SetCharacterActionState(ECharacterActionState::ECAS_Crouching);
		UnCrouch();
	}
}

void ALinariCharacter::Dodge()
{
	if (IsUnoccupied())
	{
		SetCharacterActionState(ECharacterActionState::ECAS_Dodging);
		PlayDodgeMontage();
	}
}

void ALinariCharacter::PlayDodgeMontage()
{
	if (PlayerAnimations->DodgeMontage)
	{
		PlayMontageSection(PlayerAnimations->DodgeMontage, DefaultSection);
	}
}

void ALinariCharacter::HandleInteractionKeyPressed()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->HandleInteractionKey(this);
	}
	
	if (IItemInterface* ItemInterface = Cast<IItemInterface>(OverlappingItem))
	{
		ItemInterface->HandleInteractionKey(this);
	}
}

void ALinariCharacter::Attack()
{
	if (IsUnoccupied())
	{
		PlayAttackSection();
	}
}


void ALinariCharacter::PlayAttackSection()
{
	if (EquippedWeapon && CanAttack())
	{
		PlayCombatSection(EquippedWeapon->GetCombatMontage(), EquippedWeapon->GetCombatMontageSections());
		SetCharacterActionState(ECharacterActionState::ECAS_Attacking);
	} else if (!EquippedWeapon)
	{
		PlayFistAttackSection();
	}
	
}

void ALinariCharacter::PlayFistAttackSection()
{
	if (PlayerAnimations->FistAttackMontage)
	{
		PlayCombatSection(PlayerAnimations->FistAttackMontage, FistCombatMontageSections);
	}
}

bool ALinariCharacter::CanAttack()
{
	return IsUnoccupied();
}

bool ALinariCharacter::CanEquipWeapon() const
{
	return IsUnoccupied()
		&& IsUnequipped()
		&& EquippedWeapon;
}

void ALinariCharacter::PlayEquipMontage()
{
	if (PlayerAnimations->EquipMontage)
	{
		PlayMontageSection(PlayerAnimations->EquipMontage, EquippedWeapon->GetEquipMontageSection());
		SetCharacterActionState(ECharacterActionState::ECAS_EquippingWeapon);
		SetCharacterState(ECharacterState::ELCS_EquippedWeapon);
	}
}

bool ALinariCharacter::CanDisarmWeapon() const
{
	return IsUnoccupied() && !IsUnequipped();
}

void ALinariCharacter::PlayDisarmMontage()
{
	if (PlayerAnimations->DisarmMontage)
	{
		PlayMontageSection(PlayerAnimations->DisarmMontage, EquippedWeapon->GetDisarmMontageSection());
        SetCharacterActionState(ECharacterActionState::ECAS_EquippingWeapon);
        SetCharacterState(ECharacterState::ELCS_Unequipped);
	}
}

bool ALinariCharacter::IsUnequipped() const
{
	return CharacterState == ECharacterState::ELCS_Unequipped;
}

bool ALinariCharacter::IsUnoccupied() const
{
	return CharacterActionState == ECharacterActionState::ECAS_Unoccupied;
}

bool ALinariCharacter::IsJumpAvailable() const
{
	return IsUnoccupied()
		&& bIsJumpAvailable
		&& !GetCharacterMovement()->IsCrouching();
}

void ALinariCharacter::AttachWeaponToHandSocket()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachToSocketComponent(GetMesh(), RightHandSocketName);
	}
}

void ALinariCharacter::AttachWeaponToHoldSocket()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachToSocketComponent(GetMesh(), EquippedWeapon->GetDisarmSocket());
	}
}