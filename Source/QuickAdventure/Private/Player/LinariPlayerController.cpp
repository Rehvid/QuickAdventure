// Copyright Dawid Harendarz.


#include "Player/LinariPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/LinariCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void ALinariPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);
}

void ALinariPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALinariPlayerController::Move);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &ALinariPlayerController::StartRunning);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &ALinariPlayerController::StopRunning);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALinariPlayerController::Look);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ALinariPlayerController::Jump);
}

void ALinariPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}

void ALinariPlayerController::StartRunning(const FInputActionValue& InputActionValue)
{
	if (GetCharacter())
	{
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 900.f;
	}
}

void ALinariPlayerController::StopRunning(const FInputActionValue& InputActionValue)
{
	if (GetCharacter())
	{
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 600.f;
	}
}

void ALinariPlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookVector = InputActionValue.Get<FVector2D>();
	AddPitchInput(LookVector.Y);
	AddYawInput(LookVector.X);
}

void ALinariPlayerController::Jump(const FInputActionValue& InputActionValue)
{
	if (GetCharacter())
	{
		GetCharacter()->Jump();
	}
}

void ALinariPlayerController::Crouch(const FInputActionValue& InputActionValue)
{
	//@TODO: Crouch
}

void ALinariPlayerController::Dodge(const FInputActionValue& InputActionValue)
{
	//@TODO: Dodge
}

