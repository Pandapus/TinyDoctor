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

	maxAmmo = ammo;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::MoveForward(const float value)
{
	FVector direction = FVector::ForwardVector * value;
	direction = direction.RotateAngleAxis(springArm->GetComponentRotation().Yaw, FVector::UpVector);
	AddMovementInput(direction);
}

void APlayerCharacter::MoveRight(const float value)
{
	FVector direction = FVector::RightVector * value;
	direction = direction.RotateAngleAxis(springArm->GetComponentRotation().Yaw, FVector::UpVector);
	AddMovementInput(direction);
}

void APlayerCharacter::Shoot()
{
	if (bStandardWeaponActive)
		ShootStandard();
	else
		Shotgun();
}

void APlayerCharacter::ShootStandard()
{
	const float SpawnOffset = 100.f;

	FVector direction = GetActorForwardVector();
	FVector position = GetActorLocation() + (direction * SpawnOffset);

	AProjectile* actorReference = GetWorld()->SpawnActor<AProjectile>(projectile, position, direction.Rotation());

	ammo--;
}

void APlayerCharacter::Shotgun_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Shotgun-method is not intended to be used in C++. Use a BP version of this method."));
}

bool APlayerCharacter::ChangeHealth(const float amount)
{
	health += amount;

	if (health > maxHealth)
		health = maxHealth;
	else if (health <= 0.f)
	{
		Cast<AStandardGameMode>(GetWorld()->GetAuthGameMode())->GameOver();
		return true;
	}

	return false;
}

const int APlayerCharacter::GetAmmo() { return ammo; }

const int APlayerCharacter::GetMaxAmmo() { return maxAmmo; }

int APlayerCharacter::ChangeAmmo(const int amount)
{
	ammo += amount;

	if (ammo > maxAmmo)
		ammo = maxAmmo;
	else if (ammo < 0)
		ammo = 0;

	return ammo;
}

int APlayerCharacter::DecreaseAmmo(const int amount)
{
	ChangeAmmo(-amount);

	return ammo;
}
