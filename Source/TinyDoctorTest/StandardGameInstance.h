// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "StandardGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TINYDOCTORTEST_API UStandardGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:

	void SetPlayerStats(float &playerHealth, float &playerMaxHealth, int &playerAmmo, int &playerMaxAmmo);

protected:
	// Controls whether the player should have it's stats be saved across levels. This gets set to true the first time the player spawns.
	UPROPERTY(BlueprintReadWrite)
		bool bRememberStats = false;

	UPROPERTY(BlueprintReadWrite)
		float savedHealth = 0.f;
	float savedMaxHealth = 0.f;
	UPROPERTY(BlueprintReadWrite)
		int savedAmmo = 0;
	int savedMaxAmmo = 0;

public:
	friend class APlayerCharacter;

};
