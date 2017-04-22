// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "Boss.h"

bool ABoss::TakeDamageWithKnockback(const float amount, const FVector damageOrigin, const float horizontalKnockback, const float verticalKnockback)
{
	if (bInvulnerable == false)
	{
		if (ChangeHealth(-amount))
			return true;
		else
			return false;
	}

	return false;
}

const bool ABoss::GetInvulnerable() { return bInvulnerable; }

