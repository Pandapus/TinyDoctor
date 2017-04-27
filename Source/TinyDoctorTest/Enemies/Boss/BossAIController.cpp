// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "BossAIController.h"

void ABossAIController::BeginPlay()
{
	Super::BeginPlay();

	// Temporary code.
	constexpr float activateDelay = 0.1f;
	FTimerHandle delayActivation;
	GetWorldTimerManager().SetTimer(delayActivation, this, &ABossAIController::Activate, activateDelay, false);
}

void ABossAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABossAIController::SetCharacterReference()
{
	Super::SetCharacterReference();
	characterReference = Cast<ABoss>(Super::characterReference);
}

void ABossAIController::Activate_Implementation()
{
	currentHealthStep = characterReference->numberOfHealthSteps;

	characterReference->Activate();

	StartInvulnerableMode();
}

void ABossAIController::AI()
{
	switch (aiMode)
	{
	case AIMode::Active:
		Active();
		break;
	case AIMode::Invulnerable:
		Invulnerable();
		break;
	}
}

void ABossAIController::StartActiveMode()
{
	aiMode = AIMode::Active;
	characterReference->bInvulnerable = false;
	currentHealthStep--;
	activeTargetHealth = (characterReference->GetMaxHealth() / characterReference->numberOfHealthSteps) * (currentHealthStep);
}

void ABossAIController::Active()
{
	if (characterReference->GetHealth() <= activeTargetHealth)
		StartInvulnerableMode();
}

FTimerHandle invulnerableTimerHandle;
void ABossAIController::StartInvulnerableMode()
{
	aiMode = AIMode::Invulnerable;
	characterReference->bInvulnerable = true;

	for (AMinionSpawner* minionSpawner : spawners)
		minionSpawner->StartSpawning(characterReference->amountToSpawnPerSpawner);

	constexpr float minimumInvulnerableTime = 1.f;
	GetWorld()->GetTimerManager().SetTimer(invulnerableTimerHandle, minimumInvulnerableTime, false);
}

void ABossAIController::Invulnerable()
{
	if (!GetWorld()->GetTimerManager().IsTimerActive(invulnerableTimerHandle))
	{
		if (spawnedEnemies.Num() <= 0)
		{
			StartActiveMode();
			return;
		}

		for (auto enemy : spawnedEnemies)
		{
			if (enemy->IsActorBeingDestroyed() == true)
				spawnedEnemies.RemoveSingleSwap(enemy);
		}
	}
}