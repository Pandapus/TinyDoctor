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
	
public:
	UFUNCTION(BlueprintCallable)
		void StartGame();

	UPROPERTY(BlueprintReadWrite)
		float playerHealth;
	float playerMaxHealth;

	UPROPERTY(BlueprintReadWrite)
		int playerAmmo;
	int playerMaxAmmo;

	bool bRememberStats = false;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class APlayerCharacter> playerClass;
};
