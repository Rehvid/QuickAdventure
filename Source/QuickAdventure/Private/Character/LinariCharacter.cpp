// Copyright Dawid Harendarz.

#include "Character/LinariCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Item/ItemBase.h"
#include "Item/Weapon/Weapon.h"

void ALinariCharacter::SetOverlappingItem(AItemBase* Item)
{
	OverlappingItem = Item;
}

void ALinariCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeMappingContext();
}

void ALinariCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	InitializeEnhancedInputActions(PlayerInputComponent);
}

void ALinariCharacter::InitializeMappingContext()
{
	check(MappingContext);
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		check(Subsystem);

		Subsystem->AddMappingContext(MappingContext, 0);
	}
}

void ALinariCharacter::InitializeEnhancedInputActions(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALinariCharacter::Move);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &ALinariCharacter::StartRunning);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &ALinariCharacter::StopRunning);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALinariCharacter::Look);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ALinariCharacter::Jump);
	EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &ALinariCharacter::Dodge);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ALinariCharacter::Crouch);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ALinariCharacter::UnCrouch);
	EnhancedInputComponent->BindAction(EKeyPressedAction, ETriggerEvent::Triggered, this, &ALinariCharacter::EKeyPressed);
}


void ALinariCharacter::Move(const FInputActionValue& InputActionValue)
{
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
	if (!IsRunning())
	{
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
		CharacterState = ELinariCharacterState::ELCS_Running;
	}
}

void ALinariCharacter::StopRunning()
{
	if (IsRunning())
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
		CharacterState = ELinariCharacterState::ELCS_Walking;
	}
	
}

void ALinariCharacter::Look(const FInputActionValue& InputActionValue)
{
	if (GetController())
	{
		const FVector2D LookVector = InputActionValue.Get<FVector2D>();
        AddControllerPitchInput(LookVector.Y);
        AddControllerYawInput(LookVector.X);
	}
}

void ALinariCharacter::Jump(const FInputActionValue& InputActionValue)
{
	if (GetCharacterMovement())
	{
		Super::Jump();
	}
}

void ALinariCharacter::Crouch(const FInputActionValue& InputActionValue)
{
	if (GetCharacterMovement())
	{
		Super::Crouch();
	}

}

void ALinariCharacter::UnCrouch()
{
	if (GetCharacterMovement())
	{
		Super::UnCrouch();
	}
}

void ALinariCharacter::Dodge()
{
	PlayDodgeMontage();
}

void ALinariCharacter::EKeyPressed(const FInputActionValue& InputActionValue)
{
	AWeapon* Weapon = Cast<AWeapon>(OverlappingItem);
	
	if (Weapon)
	{
		EquipWeapon(Weapon);
	}
}

void ALinariCharacter::EquipWeapon(AWeapon* Weapon)
{
	Weapon->Equip(GetMesh());
	EquippedWeapon = Weapon;
	OverlappingItem = nullptr;
}

void ALinariCharacter::PlayDodgeMontage()
{
	if (DodgeAnimMontage)
	{
		PlayMontageSection(DodgeAnimMontage, FName("Default"));
	}
}

bool ALinariCharacter::IsUnoccupied() const
{
	return CharacterState == ELinariCharacterState::ELCS_Unoccupied;
}

bool ALinariCharacter::IsRunning() const
{
	return CharacterState == ELinariCharacterState::ELCS_Running;
}

bool ALinariCharacter::IsWalking() const
{
	return CharacterState == ELinariCharacterState::ELCS_Walking;
}
