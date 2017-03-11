// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

	// Reference to the character the AIController is controlling.
	ACharacter* characterReference;

	// Position at which the enemy spawned on
	FVector originalPosition;

	// Calculates distance from enemy to player
	float DistanceToPlayer();

	// Moves characterReference to playerReference's position.
	void MoveToPlayer();
	
};
