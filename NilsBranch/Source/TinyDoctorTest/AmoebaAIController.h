// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Amoeba.h"

#include "AIController.h"
#include "AmoebaAIController.generated.h"

/**
 * 
 */
UCLASS()
class TINYDOCTORTEST_API AAmoebaAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	// Holds reference to the player-actor. This is used to calculate the objects distance to the enemy.
	AActor* playerReference;

	AAmoeba* characterReference;

	// Contains the spawn-location of the object. This allows it to return after chasing the player.
	FVector originalPosition;

	enum class AIMode {
		Patrol,
		Chase,
		Return
	};

	AIMode aiMode = AIMode::Patrol;

	bool bRoamingMovingToLocation;
	FVector targetPosition = FVector::ZeroVector;

	// Original MaxWalkSpeed of the character being controlled
	float originalWalkSpeed;

	void AI();
	void PatrolMode();
	void AIRoam();
	void ChaseMode();
	void ReturnMode();
	
};
