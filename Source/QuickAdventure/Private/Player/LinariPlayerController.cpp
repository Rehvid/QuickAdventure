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
	checkf(PlayerContext, TEXT("Linari Context is not initialzied, please fill out BP_LinariPlayerController"));
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(PlayerContext, 0);
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
	
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ALinariPlayerController::Jump);

	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ALinariPlayerController::StartCrouching);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ALinariPlayerController::StopCrouching);
	
	EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &ALinariPlayerController::Dodge);
	
	EnhancedInputComponent->BindAction(EKeyPressedAction, ETriggerEvent::Triggered, this, &ALinariPlayerController::InteractionKeyPressed);

	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ALinariPlayerController::Attack);
}

void ALinariPlayerController::Move(const FInputActionValue& InputActionValue)
{
	if (!ControlledPawn->IsUnoccupied()) return;
	
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
	if (ControlledPawn->GetMovementComponent()->IsMovingOnGround())
	{
        ControlledPawn->SetCharacterMovementMaxSpeedWalk(RunningSpeed);
	}
}

void ALinariPlayerController::StopRunning()
{
	ControlledPawn->SetCharacterMovementMaxSpeedWalk(WalkingSpeed);
}

void ALinariPlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookVector = InputActionValue.Get<FVector2D>();
	AddPitchInput(LookVector.Y);
	AddYawInput(LookVector.X);
}

void ALinariPlayerController::Jump()
{
	if (ControlledPawn->CanJump())
	{
		ControlledPawn->SetCharacterActionState(ECharacterActionState::ECAS_Jumping);
        ControlledPawn->Jump();
		ControlledPawn->SetCanJumpAgain(false);
		
		GetWorldTimerManager().SetTimer(JumpTimer, this, &ALinariPlayerController::JumpTimerFinished , WaitTimeUntilJumpAgain);
	}
}


void ALinariPlayerController::StartCrouching()
{
	if (ControlledPawn->GetMovementComponent()->IsMovingOnGround())
	{
		ControlledPawn->SetCharacterActionState(ECharacterActionState::ECAS_Crouching);
		ControlledPawn->Crouch();
	}
}

void ALinariPlayerController::StopCrouching()
{
	if (ControlledPawn->GetMovementComponent()->IsCrouching())
	{
		ControlledPawn->SetCharacterActionState(ECharacterActionState::ECAS_Crouching);
        ControlledPawn->UnCrouch();
	}
}

void ALinariPlayerController::Dodge()
{
	if (ControlledPawn->GetMovementComponent()->IsMovingOnGround())
	{
		ControlledPawn->Dodge();
	}
}

void ALinariPlayerController::InteractionKeyPressed()
{
	if (ControlledPawn->GetMovementComponent()->IsMovingOnGround() && !ControlledPawn->GetMovementComponent()->IsCrouching())
	{
		ControlledPawn->InteractionKeyPressed();
	}
}

void ALinariPlayerController::Attack()
{
	ControlledPawn->PlayAttackSection();
}

void ALinariPlayerController::SetCharacterMovementMaxWalkSpeed(const double Speed) const
{
	if (ControlledPawn->GetCharacterMovement())
	{
		ControlledPawn->GetCharacterMovement()->MaxWalkSpeed = Speed;
	}
}

void ALinariPlayerController::JumpTimerFinished()
{
	GetWorldTimerManager().ClearTimer(JumpTimer);
	ControlledPawn->SetCanJumpAgain(true);
}
