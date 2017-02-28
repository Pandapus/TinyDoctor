// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springArm->SetupAttachment(RootComponent);
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm, USpringArmComponent::SocketName);

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

void APlayerCharacter::Shoot()
{
	if (ammo > 0)
	{
		const float SpawnOffset = 100.f;

		FVector direction = GetActorForwardVector();
		FVector position = GetActorLocation() + (direction * SpawnOffset);

		AProjectile* actorReference = GetWorld()->SpawnActor<AProjectile>(projectile, position, direction.Rotation());

		ammo--;
	}
}


