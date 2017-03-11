// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class TINYDOCTORTEST_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()

protected:
	APlayerCharacterController();

private:

	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void PauseGame();

	// Movement
	void MoveForward(float value);
	void MoveRight(float value);

	// Shooting
	void Shoot();

	// Gamepad aiming
	bool bUsingGamepad = false;
	FVector gamepadAimDirection = FVector::ZeroVector;
	float gamepadActivateThreshold = 0.25f;
	void GamepadAimForward(float value);
	void GamepadAimRight(float value);
	void OrientTowardsGamepadAnalog();

	// Cursor-oriented aiming
	FVector previousMousePosition = FVector::ZeroVector;
	bool CheckForMouseMovement();
	void OrientTowardsCursor();
	
};
