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
	// Reference to the pawn that the controller is controlling.
	AAmoeba* characterReference;

	virtual void SetCharacterReference() override;

	// Original MaxWalkSpeed of the character being controlled
	float walkSpeed;

	//
	// Methods that control the AI
	//

	// Used to handle various delay effect associated with Patrol Mode usually.
	FTimerHandle delayTimerHandle;

	// Patrol Mode
	FVector targetPosition = FVector::ZeroVector;
	void StartPatrolMode();
	virtual void PatrolMode() override;
	void Roaming();
	void PickNewRoamingTargetAndMoveThere();
	FTimerHandle timerPickNewRoamingTargetInterval;

	bool CanEnemySeePlayer();

	// Chase Mode
	virtual void ChaseMode() override;
	FTimerHandle timerMoveToPlayerInterval;

public:
	UFUNCTION(BlueprintCallable)
		void StartChaseMode();
	
	friend class AAmoeba;
};
