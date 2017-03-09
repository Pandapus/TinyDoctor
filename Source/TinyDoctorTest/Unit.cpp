// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "Unit.h"


// Sets default values
AUnit::AUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();

	maxHealth = health;
}

// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnit::ReduceHealth(float amount, AActor* damageCauser, float horizontalKnockback, float verticalKnockback)
{
	health -= amount;

	// If the unit is has too little health, kill it (with fire!!!)
	if (health <= 0.f)
	{
		Destroy();
		return;
	}

	FVector pushVector = FVector(GetActorLocation() - damageCauser->GetActorLocation());
	pushVector.Z = 0.f;
	pushVector.Normalize();
	pushVector.X *= horizontalKnockback;
	pushVector.Y *= horizontalKnockback;
	pushVector.Z = verticalKnockback;
	LaunchCharacter(pushVector, true, true);
}

