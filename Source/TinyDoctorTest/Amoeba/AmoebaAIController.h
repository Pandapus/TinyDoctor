// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Amoeba.h"

#include "BaseAIController.h"
#include "AmoebaAIController.generated.h"

/**
 * 
 */
UCLASS()
class TINYDOCTORTEST_API AAmoebaAIController : public ABaseAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	// Reference to the Ameoba-character that the controller is controlling.
	AAmoeba* characterReference;

	// Original MaxWalkSpeed of the character being controlled
	float walkSpeed;

	//
	// Methods that control the AI
	//

	FTimerHandle delayTimerHandle;

	// Patrol Mode
	FVector targetPosition = FVector::ZeroVector;
	void StartPatrolMode();
	virtual void PatrolMode() override;
	void Roaming();
	void PickNewRoamingTargetAndMoveThere();

	bool CanEnemySeePlayer();

	// Chase Mode
	virtual void ChaseMode() override;
public:
	void StartChaseMode();
	
	
};
