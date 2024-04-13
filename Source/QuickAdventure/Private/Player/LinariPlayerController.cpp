// Copyright Dawid Harendarz.


#include "Player/LinariPlayerController.h"

#include "Character/LinariCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void ALinariPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ControlledPawn = GetPawn<ALinariCharacter>();
	
	checkf(ControlledPawn, TEXT("Linari Character class is not initialzied"));
	checkf(LinariContext, TEXT("Linari Context is not initialzied, please fill out BP_LinariPlayerController"));
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(LinariContext, 0);
	}
}

void ALinariPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALinariPlayerController::Move);
	
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &ALinariPlayerController::StartRunning);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &ALinariPlayerController::StopRunning);
	
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALinariPlayerController::Look);
	
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ALinariPlayerController::StartJump);

	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ALinariPlayerController::StartCrouching);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ALinariPlayerController::StopCrouching);
	
	EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &ALinariPlayerController::Dodge);
	
	EnhancedInputComponent->BindAction(EKeyPressedAction, ETriggerEvent::Triggered, this, &ALinariPlayerController::EKeyPressed);
}

void ALinariPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
	ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
}

void ALinariPlayerController::StartRunning()
{
	if (ControlledPawn->GetCharacterMovement())
	{
		ControlledPawn->GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	}
}

void ALinariPlayerController::StopRunning()
{
	if (ControlledPawn->GetCharacterMovement())
	{
		ControlledPawn->GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	}
}

void ALinariPlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookVector = InputActionValue.Get<FVector2D>();
	AddPitchInput(LookVector.Y);
	AddYawInput(LookVector.X);
}

void ALinariPlayerController::StartJump()
{
	ControlledPawn->Jump();
}

void ALinariPlayerController::StartCrouching()
{
	ControlledPawn->Crouch();
}

void ALinariPlayerController::StopCrouching()
{
	ControlledPawn->UnCrouch();
}

void ALinariPlayerController::Dodge()
{
	ControlledPawn->Dodge();
}

void ALinariPlayerController::EKeyPressed()
{
	ControlledPawn->EKeyPressed();
}
