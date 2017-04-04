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

const float AUnit::GetHealth() { return health; }

const float AUnit::GetMaxHealth() { return maxHealth; }

bool AUnit::TakeDamageWithKnockback(const float amount, const FVector damageOrigin, float horizontalKnockback, float verticalKnockback)
{
	if (ChangeHealth(-amount) == false)
	{
		FVector pushVector = FVector(GetActorLocation() - damageOrigin);
		pushVector.Z = 0.f;
		pushVector.Normalize();
		pushVector.X *= horizontalKnockback;
		pushVector.Y *= horizontalKnockback;
		pushVector.Z = verticalKnockback;
		LaunchCharacter(pushVector, true, true);

		return false;
	}
	else
		return true;
}

bool AUnit::DecreaseHealth(const float amount, float &newHealth)
{
	bool bResult = ChangeHealth(-amount);

	newHealth = GetHealth();

	return bResult;
}

bool AUnit::ChangeHealth(const float amount, float &newHealth)
{
	bool bResult = ChangeHealth(amount);

	newHealth = GetHealth();

	return bResult;
}

bool AUnit::ChangeHealth(const float amount)
{
	health += amount;

	if (health > maxHealth)
		health = maxHealth;
	else if (health <= 0.f)
	{
		health = 0.f;
		Destroy();
		return true;
	}

	return false;
}