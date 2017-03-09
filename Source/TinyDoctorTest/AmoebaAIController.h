// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Includes the "AAmoeba"-class
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

	// Reference to the Ameoba-character that the controller is controlling.
	AAmoeba* characterReference;

	// Original MaxWalkSpeed of the character being controlled
	float walkSpeed;

	// Calculates distance from enemy to player
	float DistanceToPlayer();


	//
	// Methods that control the AI
	//
	enum class AIMode {
		Patrol,
		Chase
	};

	AIMode aiMode;
	void AI();

	FTimerHandle delayTimerHandle;

	// Patrol Mode
	FVector originalPosition;
	FVector targetPosition = FVector::ZeroVector;
	void StartPatrolMode();
	void PatrolMode();
	void Roaming();
	void PickNewRoamingTargetAndMoveThere();

	// Chase Mode
	void ChaseMode();
public:
	void StartChaseMode();
	void MoveToPlayer();
};
