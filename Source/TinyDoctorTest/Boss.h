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

	virtual bool TakeDamageWithKnockback(const float amount, const FVector damageOrigin, const float horizontalKnockback, const float verticalKnockback) override;

	bool bInvulnerable = false;

protected:
	UPROPERTY(EditAnywhere, Category = "Stats")
		int numberOfHealthSteps = 3;

	UFUNCTION(BlueprintPure)
		const bool GetInvulnerable();


public:

	friend class ABossAIController;
};
