// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Virus.h"

#include "Enemies/BaseAIController.h"
#include "VirusAIController.generated.h"

/**
 * 
 */
UCLASS()
class TINYDOCTORTEST_API AVirusAIController : public ABaseAIController
{
	GENERATED_BODY()

private:
	AVirus* characterReference;
	virtual void SetCharacterReference() override;

	class AVirusSpawner* spawnerReference;
	void RemoveSelfFromSpawnerArray();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	virtual void PatrolMode() override;
	FTimerHandle timerMoveToPlayerManager;
	void StartChaseMode();
	virtual void ChaseMode() override;

public:
	friend class AVirusSpawner;
	friend class AVirus;
	
};
