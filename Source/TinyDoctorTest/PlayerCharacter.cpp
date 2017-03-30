// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "PlayerCharacter.h"

#include "Projectile.h"
#include "StandardGameMode.h"

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

	// Finds components on the Blueprint Class
	springArm = FindComponentByClass<USpringArmComponent>();
	//camera = FindComponentByClass<UCameraComponent>();

	maxAmmo = ammo;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::MoveForward(float value)
{
	FVector direction = FVector::ForwardVector * value;
	direction = direction.RotateAngleAxis(springArm->GetComponentRotation().Yaw, FVector::UpVector);
	AddMovementInput(direction);
}

void APlayerCharacter::MoveRight(float value)
{
	FVector direction = FVector::RightVector * value;
	direction = direction.RotateAngleAxis(springArm->GetComponentRotation().Yaw, FVector::UpVector);
	AddMovementInput(direction);
}

void APlayerCharacter::Shoot_Implementation()
{
	// Insert warning here
}

void APlayerCharacter::ShootStandard()
{
	const float SpawnOffset = 100.f;

	FVector direction = GetActorForwardVector();
	FVector position = GetActorLocation() + (direction * SpawnOffset);

	AProjectile* actorReference = GetWorld()->SpawnActor<AProjectile>(projectile, position, direction.Rotation());

	ammo--;
}


