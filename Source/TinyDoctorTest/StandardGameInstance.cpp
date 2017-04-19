// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "StandardGameInstance.h"

void UStandardGameInstance::StartGame()
{
	playerMaxHealth = playerHealth;
	playerMaxAmmo = playerAmmo;

	bRememberStats = true;
}


