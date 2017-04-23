// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unit.h"
#include "Boss.generated.h"

/**
 * 
 */
UCLASS()
class TINYDOCTORTEST_API ABoss : public AUnit
{
	GENERATED_BODY()
	
private:

	virtual void Destroyed() override;

	virtual bool TakeDamageWithKnockback(const float amount, const FVector damageOrigin, const float horizontalKnockback, const float verticalKnockback) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Stats")
		int numberOfHealthSteps = 3;

	UPROPERTY(EditAnywhere, Category = "Stats")
		int amountToSpawnPerSpawner = 2;

	UFUNCTION(BlueprintNativeEvent)
		void Activate();


public:

	friend class ABossAIController;
};
