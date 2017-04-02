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
	~ABaseAIController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Holds reference to the player's actor
	static AActor* playerReference;

	// Reference to the character the AIController is controlling.
	AEnemy* characterReference;

	virtual void SetCharacterReference();

	// Position at which the enemy spawned on
	FVector originalPosition;

	const FVector GetVectorToPlayer();

	// Calculates distance from enemy to player
	const float DistanceToPlayer();

	enum class AIMode {
		Patrol,
		Chase
	};

	AIMode aiMode = AIMode::Patrol;

	// Switch that calls correct method depending on aiMode
	virtual void AI();
	virtual void PatrolMode();
	virtual void ChaseMode();

	// Moves characterReference to playerReference's position.
	void MoveToPlayer();
	
};
