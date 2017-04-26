// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "PlayerCharacter.h"

#include "Projectile.h"
#include "StandardGameMode.h"
#include "StandardGameInstance.h"

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

	Cast<UStandardGameInstance>(GetWorld()->GetGameInstance())->SetPlayerStats(health, maxHealth, ammo, maxAmmo);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool APlayerCharacter::TakeDamageWithKnockback(const float amount, const FVector damageOrigin, const float horizontalKnockback, const float verticalKnockback)
{
	if (Super::TakeDamageWithKnockback(amount, damageOrigin, horizontalKnockback, verticalKnockback) == false)
	{
		bInvulnerable = true;

		constexpr float invulnerableLengthInSeconds = 0.1f;

		FTimerHandle invulnerablePeriod;
		GetWorldTimerManager().SetTimer(invulnerablePeriod, this, &APlayerCharacter::SetInvulnerableToFalse, invulnerableLengthInSeconds);
	}
	return false;
}

void APlayerCharacter::SetInvulnerableToFalse() { bInvulnerable = false; }

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
	if (IsRifleActive() && GetAmmo() > rifleCost)
	{
		ShootRifle();
		DecreaseAmmo(rifleCost);
	}
	else if (!IsRifleActive() && GetAmmo() > shotgunCost)
	{
		ShootShotgun();
		DecreaseAmmo(shotgunCost);
	}
}

void APlayerCharacter::ShootRifle()
{
	constexpr float SpawnOffset = 150.f;

	FVector direction = GetActorForwardVector();
	FVector position = GetActorLocation() + (direction * SpawnOffset);

	AProjectile* projectileReference = GetWorld()->SpawnActor<AProjectile>(projectileToShoot, position, direction.Rotation());
}

void APlayerCharacter::ShootShotgun_Implementation()
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

const bool APlayerCharacter::IsRifleActive() { return bRifleActive; }

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

void APlayerCharacter::WeaponChangeEvent_Implementation() {}