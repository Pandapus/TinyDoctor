// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy.h"

#include "AIController.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class TINYDOCTORTEST_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Holds reference to the player's actor
	AActor* playerReference;
	
	// Switch that calls correct method depending on aiMode
	virtual void AI();
	virtual void PatrolMode();
	virtual void ChaseMode();

public:

	enum class AIMode {
		Patrol,
		Chase
	};

	AIMode aiMode = AIMode::Patrol;

	// Reference to the character the AIController is controlling.
	AEnemy* characterReference;

	// Position at which the enemy spawned on
	FVector originalPosition;

	// Calculates distance from enemy to player
	float DistanceToPlayer();
	
	// Moves characterReference to playerReference's position.
	void MoveToPlayer();
};
