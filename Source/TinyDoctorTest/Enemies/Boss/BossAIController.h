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

	TArray<AMinionSpawner*> spawners;

	int currentHealthStep;
	float activeTargetHealth;

	enum class AIMode {
		Inactive,
		Active,
		Invulnerable
	};

	AIMode aiMode = AIMode::Inactive;

	virtual void AI() override;

	void StartActiveMode();
	void Active();

	void StartInvulnerableMode();
	void Invulnerable();

protected:
	UPROPERTY(BlueprintReadOnly)
		ABoss* characterReference;

	UPROPERTY(BlueprintReadWrite)
		TArray<AActor*> spawnedEnemies;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void Activate();

public:
	friend class AMinionSpawner;
};
