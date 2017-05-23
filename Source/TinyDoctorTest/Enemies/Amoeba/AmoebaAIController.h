// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Amoeba.h"

#include "Enemies/BaseAIController.h"
#include "AmoebaAIController.generated.h"

/**
 * 
 */
UCLASS()
class TINYDOCTORTEST_API AAmoebaAIController : public ABaseAIController
{
	GENERATED_BODY()

protected:
	AAmoebaAIController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	// Reference to the pawn that the controller is controlling.
	AAmoeba* characterReference;
	virtual void SetCharacterReference() override;

	//
	// Methods that control the AI
	//
	
	FTimerHandle waitingTimerHandle;
	FTimerHandle intervalCallSafetyTimerHandle;

	enum class AIMode {
		Patrol,
		Chase
	};

	AIMode aiMode = AIMode::Patrol;

	void AI();

	// Patrol Mode
	void StartPatrolMode();
	void PatrolMode();
	void Roaming();
	void PickNewRoamingTargetAndMoveThere();
	bool CanEnemySeePlayer();

	// Chase Mode
	void ChaseMode();

public:
	UFUNCTION(BlueprintCallable)
		void StartChaseMode();
	
	friend class AAmoeba;
};
