#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "SKCharacter.generated.h"

class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;

struct FInputActionValue;

UCLASS(config=Game)
class ASKCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ASKCharacter();

	virtual void Tick(float DeltaTime) override;

	void StartJump(const FInputActionValue& Value);

	void SpeedUp();

	virtual void Landed(const FHitResult& Hit) override;

	USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);

	void RotateCamera(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* LookAction;

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

