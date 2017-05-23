// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "StandardGameInstance.h"

void UStandardGameInstance::SetPlayerStats(float &health, float &maxHealth, int &ammo, int &maxAmmo)
{
	// If bRememberStats is true, the player will read stats.
	// If not it will set the stats.
	if (bRememberStats == true)
	{
		health = savedHealth;
		maxHealth = savedMaxHealth;
		ammo = savedAmmo;
		maxAmmo = savedMaxAmmo;
	}
	else
	{
		maxAmmo = ammo;

		savedHealth = health;
		savedMaxHealth = maxHealth;
		savedAmmo = ammo;
		savedMaxAmmo = maxAmmo;

		bRememberStats = true;
	}
}


