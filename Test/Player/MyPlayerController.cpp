// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject2.h"
#include "MyPlayerController.h"

#include "TimerManager.h"

// Includes class of Main Character
#include "PlayerClass.h"

// Includes projectile that gets shot by character
#include "MyProjectile.h"

AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;
}

void AMyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	OrientTowardsCursor();
}

void AMyPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up gameplay key bindings
	InputComponent->BindAxis("MoveForward", this, &AMyPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyPlayerController::MoveRight);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &AMyPlayerController::Shoot);

}

void AMyPlayerController::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		const FVector Direction = FVector(1.0f, 0.0f, 0.0f);
		ACharacter* MyCharacter = GetCharacter();
		MyCharacter->AddMovementInput(Direction, Value);
	}
}

void AMyPlayerController::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		const FVector Direction = FVector(0.0f, 1.0f, 0.0f);
		ACharacter* MyCharacter = GetCharacter();
		MyCharacter->AddMovementInput(Direction, Value);
	}
}

void AMyPlayerController::OrientTowardsCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit) // Something was hit
	{
		ACharacter* MyCharacter = GetCharacter();

		FVector impactVector = Hit.ImpactPoint;

		FVector targetVector = impactVector - MyCharacter->GetActorLocation();
		
		FRotator newRotation = MyCharacter->GetActorRotation();
		newRotation.Yaw = targetVector.Rotation().Yaw;

		MyCharacter->SetActorRotation(newRotation);
		FacingDirection = targetVector;
	}
}

void AMyPlayerController::Shoot()
{
	UE_LOG(LogTemp, Warning, TEXT("Shoot-function started."));
	if (bCanFire)
	{
		const FRotator FireRotation = FacingDirection.Rotation();
		// Spawn projectile at an offset from this pawn
		const FVector SpawnLocation = GetCharacter()->GetActorLocation() + FireRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			// spawn the projectile
			World->SpawnActor<AMyProjectile>(SpawnLocation, FireRotation);
		}

		bCanFire = false;
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AMyPlayerController::ShotTimerExpired, FireRate);
	}
}

void AMyPlayerController::ShotTimerExpired()
{
	bCanFire = true;
}

