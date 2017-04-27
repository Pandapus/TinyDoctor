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
	
protected:
	AEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
		float detectionRadius = 1500.f;
	
public:
	friend class ABaseAIController;
};
