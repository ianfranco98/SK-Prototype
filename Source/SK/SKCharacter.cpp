#include "SKCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "SKObstacleDetectionComponent.h"

ASKCharacter::ASKCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 1300.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	ObstacleDetectionComponent = CreateDefaultSubobject<USKObstacleDetectionComponent>(TEXT("ObstacleDetectionComponent"));
	ObstacleDetectionComponent->SetupAttachment(RootComponent);
}

void ASKCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ASKCharacter::StartJump);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASKCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASKCharacter::RotateCamera);
	}
}

void ASKCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bSpeedUpInProgress)
	{
		CurrentAcceleration -= DecelerationFactor * DeltaTime;
	}

	CurrentAcceleration = FMath::Clamp(CurrentAcceleration, 0.0f, 1.0f);

	AddMovementInput(GetActorForwardVector(), CurrentAcceleration);
}

void ASKCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PrevCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PrevCustomMode);

	if (bPressedJump)
	{
		OnCharacterIsJumping.Broadcast(true);
	}
}

void ASKCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FVector RightVector = GetActorForwardVector().RotateAngleAxis(90.0f, FVector::ZAxisVector);
	AddMovementInput(RightVector, MovementVector.X * TurningRate);

	if (MovementVector.Y > AccelerationInputThreshold)
	{
		bSpeedUpInProgress = true;
	}
}

void ASKCharacter::SpeedUp()
{
	CurrentAcceleration += AccelerationGainedPerPush;
	bSpeedUpInProgress = false;
}

void ASKCharacter::StartJump(const FInputActionValue& Value)
{
	bJumpInProgress = Value.Get<bool>();

	// We want to cancel accel kick if we're jumping.
	if (bJumpInProgress)
	{
		bSpeedUpInProgress = false;
	}
}

void ASKCharacter::RotateCamera(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASKCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	bJumpInProgress = false;

	bWasLanded = true;

	GetWorldTimerManager().SetTimerForNextTick([this]()
	{
		bWasLanded = false;
	});

	OnCharacterIsJumping.Broadcast(false);
}