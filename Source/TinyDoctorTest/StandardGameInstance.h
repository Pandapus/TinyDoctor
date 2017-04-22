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
	bool bRememberStats = false;

	void SetPlayerStats(float &playerHealth, float &playerMaxHealth, int &playerAmmo, int &playerMaxAmmo);

protected:
	UPROPERTY(BlueprintReadWrite)
		float savedHealth = 0.f;
	float savedMaxHealth = 0.f;
	UPROPERTY(BlueprintReadWrite)
		int savedAmmo = 0;
	int savedMaxAmmo = 0;

public:
	friend class APlayerCharacter;

};
