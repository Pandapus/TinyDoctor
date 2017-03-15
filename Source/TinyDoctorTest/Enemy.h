// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unit.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class TINYDOCTORTEST_API AEnemy : public AUnit
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		float detectionRadius = 1500.f;
	
	
};
