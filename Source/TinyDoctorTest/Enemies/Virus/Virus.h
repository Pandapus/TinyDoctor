// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemies/Enemy.h"
#include "Virus.generated.h"

/**
 * 
 */
UCLASS()
class TINYDOCTORTEST_API AVirus : public AEnemy
{
	GENERATED_BODY()
	
private:
	virtual bool TakeDamageWithKnockback(const float amount, const FVector damageOrigin, const float horizontalKnockback, const float verticalKnockback) override;

	virtual void Destroyed() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		float jumpDistanceThreshold = 500.f;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		float verticalJumpStrength = 1000.f;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		float horizontalJumpStrength = 1000.f;

public:
	friend class AVirusAIController;
};
