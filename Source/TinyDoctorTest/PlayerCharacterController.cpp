// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "PlayerCharacterController.h"

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
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	playerReference = Cast<APlayerCharacter>(GetCharacter());
}

void APlayerCharacterController::Tick(float DeltaTime)
{
	if (bUsingGamepad && CheckForMouseMovement())
		bUsingGamepad = false;
	
	if (!bUsingGamepad)
		OrientTowardsCursor();
	else
		OrientTowardsGamepadAnalog();
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
	// Runs Shoot-method on the possessed Character.
	playerReference->Shoot();
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

		/*
		// Aiming-correction prototype (trigonometry)
		// Finds the angle between the camera and the hitPoint.
		float heightDifferenceBetweenPointAndCamera = playerReference->camera->GetComponentLocation().Z - Hit.ImpactPoint.Z;
		float lengthDifference = Hit.ImpactPoint.X - playerReference->camera->GetComponentLocation().X;
		float angleY = FMath::Atan(heightDifferenceBetweenPointAndCamera / lengthDifference) / PI * 180.f;

		float heightDifference = Hit.ImpactPoint.Z - playerReference->GetActorLocation().Z;

		INSERT CORRECTION CODE HERE
		
		UE_LOG(LogTemp, Warning, TEXT("Angle is %f"), angleY);
		UE_LOG(LogTemp, Warning, TEXT("HeightDifference is %f"), heightDifference);
		*/

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
		}
	}
}

void APlayerCharacterController::OrientTowardsGamepadAnalog()
{
	ControlRotation.Yaw = gamepadAimDirection.Rotation().Yaw + 90.f + playerReference->springArm->GetComponentRotation().Yaw;
}