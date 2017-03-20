// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "PlayerCharacterController.h"

#include "PlayerCharacter.h"
#include "StandardGameMode.h"

APlayerCharacter* playerReference;

constexpr float gamepadActivateThreshold = 0.25f;
FVector gamepadAimDirection = FVector::ZeroVector;
FVector previousMousePosition = FVector::ZeroVector;

APlayerCharacterController::APlayerCharacterController()
{
	bShowMouseCursor = true;
}

// Called to bind functionality to input
void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Movement bindings
	InputComponent->BindAxis("MoveForward", this, &APlayerCharacterController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacterController::MoveRight);
	InputComponent->BindAxis("GamepadAimForward", this, &APlayerCharacterController::GamepadAimForward);
	InputComponent->BindAxis("GamepadAimRight", this, &APlayerCharacterController::GamepadAimRight);
	
	// Actions binding
	InputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerCharacterController::Shoot);
	InputComponent->BindAction("Pause", IE_Pressed, this, &APlayerCharacterController::PauseGame).bExecuteWhenPaused = true;

	InputComponent->BindAction("Choose Standard Weapon", IE_Pressed, this, &APlayerCharacterController::SetStandardWeaponActive);
	InputComponent->BindAction("Choose Shotgun", IE_Pressed, this, &APlayerCharacterController::SetShotgunWeaponActive);
}

void APlayerCharacterController::SetShotgunWeaponActive()
{
	playerReference->bStandardWeaponActive = false;
}

void APlayerCharacterController::SetStandardWeaponActive()
{
	playerReference->bStandardWeaponActive = true;
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	playerReference = Cast<APlayerCharacter>(GetCharacter());
}

void APlayerCharacterController::Tick(float DeltaTime)
{
	if (bUsingGamepad && CheckForMouseMovement())
	{
		bUsingGamepad = false;
		bShowMouseCursor = true;
	}

	if (!bUsingGamepad)
		OrientTowardsCursor();
	else
		OrientTowardsGamepadAnalog();
}

void APlayerCharacterController::PauseGame()
{
	Cast<AStandardGameMode>(GetWorld()->GetAuthGameMode())->PauseGame();
}

void APlayerCharacterController::MoveForward(float value)
{
	playerReference->MoveForward(value);
}

void APlayerCharacterController::MoveRight(float value)
{
	playerReference->MoveRight(value);
}

void APlayerCharacterController::Shoot()
{
	static FTimerHandle shootCooldownTimerHandle;

	if (!GetWorldTimerManager().IsTimerActive(shootCooldownTimerHandle))
	{
		playerReference->Shoot();
		GetWorldTimerManager().SetTimer(shootCooldownTimerHandle, playerReference->weaponCooldown, false);
	}
}

bool APlayerCharacterController::CheckForMouseMovement()
{
	FVector currentMousePosition;
	GetMousePosition(currentMousePosition.X, currentMousePosition.Y);
	if (currentMousePosition.X != previousMousePosition.X || currentMousePosition.Y != currentMousePosition.Y)
		return true;
	return false;
}

void APlayerCharacterController::OrientTowardsCursor()
{
	// Class that holds information about the object it hit.
	FHitResult Hit;
	// Ray-traces to the object under the cursor and places it in the Hit-variable above.
	if (GetHitResultUnderCursor(ECC_GameTraceChannel1, false, Hit))
	{
		// Calculates the vector between the actor and the point of impact caused by the ray-trace
		FVector targetVector = Hit.ImpactPoint - playerReference->GetActorLocation();

		ControlRotation.Yaw = targetVector.Rotation().Yaw;
	}
}

void APlayerCharacterController::GamepadAimForward(float value)
{
	if (bUsingGamepad)
		gamepadAimDirection.X = value;
	else
	{
		// Checks whether to activate controller-aiming
		if (value >= gamepadActivateThreshold)
		{
			bUsingGamepad = true;
			GetMousePosition(previousMousePosition.X, previousMousePosition.Y);
			bShowMouseCursor = false;
		}
	}
}

void APlayerCharacterController::GamepadAimRight(float value)
{
	if (bUsingGamepad)
		gamepadAimDirection.Y = value;
	else
	{
		// Checks whether to activate controller-aiming
		if (value >= gamepadActivateThreshold)
		{
			bUsingGamepad = true;
			GetMousePosition(previousMousePosition.X, previousMousePosition.Y);
			bShowMouseCursor = false;
		}
	}
}

void APlayerCharacterController::OrientTowardsGamepadAnalog()
{
	const float gamepadDeadzone = 0.5f;
	if (gamepadAimDirection.Size() >= gamepadDeadzone)
		ControlRotation.Yaw = gamepadAimDirection.Rotation().Yaw + 90.f + playerReference->springArm->GetComponentRotation().Yaw;
}