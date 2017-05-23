// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemies/Boss/Boss.h"
#include "Enemies/Boss/MinionSpawner.h"

#include "Enemies/BaseAIController.h"
#include "BossAIController.generated.h"

/**
 * 
 */
UCLASS()
class TINYDOCTORTEST_API ABossAIController : public ABaseAIController
{
	GENERATED_BODY()

private:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetCharacterReference() override;

	// Contains reference to its spawners.
	TArray<AMinionSpawner*> spawners;

	int currentHealthStep;
	float activeTargetHealth;

	enum class AIMode {
		Inactive,
		Active,
		Invulnerable
	};

	AIMode aiMode = AIMode::Inactive;

	// Switch that selects correct behaviour depending on the aiMode variable.
	void AI();

	void StartActiveMode();
	void Active();

	void StartInvulnerableMode();
	void Invulnerable();

protected:
	// Contains reference to the actor the controller is controlling.
	UPROPERTY(BlueprintReadOnly)
		ABoss* characterReference;

	// Contains reference to every actor spawned by the MinionSpawners. When invulnerable, it checks the length of this
	// array every tick to see if the player killed all of these units.
	UPROPERTY(BlueprintReadWrite)
		TArray<AActor*> spawnedEnemies;

	// Starts the boss
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void Activate();

public:
	friend class AMinionSpawner;
};
