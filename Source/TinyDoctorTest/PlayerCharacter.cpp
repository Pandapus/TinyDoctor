// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	maxAmmo = ammo;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::MoveX(float value)
{
	AddMovementInput(FVector(value, 0.0f, 0.0f));
}

void APlayerCharacter::MoveY(float value)
{
	AddMovementInput(FVector(0.0f, value, 0.0f));
}

void APlayerCharacter::Shoot()
{
	if (ammo > 0)
	{
		const float SpawnOffset = 100.0f;

		FVector direction = GetActorForwardVector();
		FVector position = GetActorLocation() + (direction * SpawnOffset);

		AProjectile* actorReference = GetWorld()->SpawnActor<AProjectile>(projectile, position, direction.Rotation());

		ammo--;
	}
}