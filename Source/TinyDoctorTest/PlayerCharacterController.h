// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerCharacter.h"

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

	APlayerCharacter* playerReference;

	void MoveX(float value);
	void MoveY(float value);
	void Shoot();

	void OrientTowardsCursor();
};
