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
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	// Reference to the pawn that the controller is controlling.
	AAmoeba* characterReference;
	virtual void SetCharacterReference() override;

	//
	// Methods that control the AI
	//

	// Patrol Mode
	void StartPatrolMode();
	virtual void PatrolMode() override;
	void Roaming();
	void PickNewRoamingTargetAndMoveThere();
	bool CanEnemySeePlayer();

	// Chase Mode
	virtual void ChaseMode() override;

public:
	UFUNCTION(BlueprintCallable)
		void StartChaseMode();
	
	friend class AAmoeba;
};
