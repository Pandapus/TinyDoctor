// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "Boss.h"

#include "StandardGameMode.h"

void ABoss::Destroyed()
{
	auto gameModeRef = Cast<AStandardGameMode>(GetWorld()->GetAuthGameMode());
	if (gameModeRef != nullptr)
		gameModeRef->GameWon();

	Super::Destroyed();
}

bool ABoss::TakeDamageWithKnockback(const float amount, const FVector damageOrigin, const float horizontalKnockback, const float verticalKnockback)
{
	if (IsInvulnerable() == false)
	{
		if (ChangeHealth(-amount) == true)
			return true;
		else
			return false;
	}
	else
		return false;
}

void ABoss::Activate_Implementation() {}

