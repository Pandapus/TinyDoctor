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
	void MoveForward(const float value);
	void MoveRight(const float value);

	// Shooting
	void Shoot();

	void SetRifleActive();
	void SetShotgunActive();

	// Gamepad aiming
	bool bUsingGamepad = false;
	void GamepadAimForward(const float value);
	void GamepadAimRight(const float value);
	void OrientTowardsGamepadAnalog();

	// Cursor-oriented aiming
	const bool CheckForMouseMovement();
	void OrientTowardsCursor();
	
};
