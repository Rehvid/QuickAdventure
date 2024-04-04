// Copyright Dawid Harendarz.

#include "Character/LinariCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


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

void ALinariCharacter::StartRunning(const FInputActionValue& InputActionValue)
{
}

void ALinariCharacter::StopRunning(const FInputActionValue& InputActionValue)
{
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
	Super::Jump();
}

void ALinariCharacter::Crouch(const FInputActionValue& InputActionValue)
{
}

void ALinariCharacter::Dodge(const FInputActionValue& InputActionValue)
{
}

void ALinariCharacter::PlayDodgeMontage(FName SectionName)
{
}
