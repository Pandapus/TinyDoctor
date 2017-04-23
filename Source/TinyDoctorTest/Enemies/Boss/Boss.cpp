// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "Boss.h"

#include "StandardGameMode.h"

void ABoss::Destroyed()
{
	Super::Destroyed();

	Cast<AStandardGameMode>(GetWorld()->GetAuthGameMode())->GameWon();
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

	return false;
}

void ABoss::Activate_Implementation() {}

