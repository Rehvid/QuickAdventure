// Copyright Dawid Harendarz.


#include "Player/LinariPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/LinariCharacter.h"

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

