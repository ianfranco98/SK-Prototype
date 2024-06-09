#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "SKCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FCharacterIsJumping, bool)

class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;

class USKObstacleDetectionComponent;

struct FInputActionValue;

UCLASS(config=Game)
class ASKCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ASKCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PrevCustomMode) override;

	void StartJump(const FInputActionValue& Value);

	void SpeedUp();

	virtual void Landed(const FHitResult& Hit) override;

	USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FCharacterIsJumping OnCharacterIsJumping;

protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);

	void RotateCamera(const FInputActionValue& Value);

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USKObstacleDetectionComponent> ObstacleDetectionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	float AccelerationInputThreshold = 0.1f;

	UPROPERTY(EditDefaultsOnly, Category = SkateMovement)
	float TurningRate = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = SkateMovement)
	float AccelerationGainedPerPush = 0.33f;

	UPROPERTY(EditDefaultsOnly, Category = SkateMovement)
	float DecelerationFactor = 0.15f;

	UPROPERTY(Transient, BlueprintReadOnly)
	bool bJumpInProgress = false;
	
	UPROPERTY(Transient, BlueprintReadOnly)
	bool bSpeedUpInProgress = false;

	UPROPERTY(Transient, BlueprintReadOnly)
	bool bWasLanded = false;

	float CurrentAcceleration = 0.0f;
};

