// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Virus.h"

#include "Enemies/BaseAIController.h"
#include "VirusAIController.generated.h"

class AVirusSpawner;

/**
 * 
 */
UCLASS()
class TINYDOCTORTEST_API AVirusAIController : public ABaseAIController
{
	GENERATED_BODY()

private:
	// Reference to the actor it is controlling.
	AVirus* characterReference;
	virtual void SetCharacterReference() override;

	// Reference to the actor the Virus was spawned by.
	AVirusSpawner* spawnerReference;
	void RemoveSelfFromSpawnerArray();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	enum class AIMode {
		Wait,
		Chase
	};

	AIMode aiMode = AIMode::Wait;

	void AI();
	void WaitMode();
	void StartChaseMode();
	void ChaseMode();

public:
	friend AVirusSpawner;
	friend AVirus;
	
};
