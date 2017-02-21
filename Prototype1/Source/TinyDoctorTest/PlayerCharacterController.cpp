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
	InputComponent->BindAxis("MoveX", this, &APlayerCharacterController::MoveX);
	InputComponent->BindAxis("MoveY", this, &APlayerCharacterController::MoveY);

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
	OrientTowardsCursor();
}

void APlayerCharacterController::MoveX(float value)
{
	playerReference->MoveX(value);
}

void APlayerCharacterController::MoveY(float value)
{
	playerReference->MoveY(value);
}

void APlayerCharacterController::Shoot()
{
	// Runs Shoot-method on the possessed Character.
	playerReference->Shoot();
}

void APlayerCharacterController::OrientTowardsCursor()
{
	// Class that holds information about the object it hit.
	FHitResult Hit;
	// Ray-traces to the object under the cursor and places it in the Hit-variable above.
	if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
	{
		// Calculates the vector between the actor and the point of impact caused by the ray-trace
		FVector targetVector = Hit.ImpactPoint - playerReference->GetActorLocation();

		ControlRotation = targetVector.Rotation();
	}
}