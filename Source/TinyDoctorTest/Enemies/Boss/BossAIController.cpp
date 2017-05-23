// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "BossAIController.h"

void ABossAIController::BeginPlay()
{
	Super::BeginPlay();

	// Minion spawners need to place themselves in this class' minionSpawner-array. This delays the boss'
	// startup in case some MinionSpawner's BeginPlay ran after this.
	constexpr float activateDelay = 0.1f;
	FTimerHandle delayActivation;
	GetWorldTimerManager().SetTimer(delayActivation, this, &ABossAIController::Activate, activateDelay, false);
}

void ABossAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AI();
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

	// Could possibly turn this logic into function pointers rather than switch.
}

void ABossAIController::StartActiveMode()
{
	aiMode = AIMode::Active;
	characterReference->bInvulnerable = false;
	currentHealthStep--;

	// Calculates the target health the player must reach in order for the boss to switch mode again.
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

	// Tells the minionspawners to spawn enemies.
	for (auto minionSpawner : spawners)
		minionSpawner->StartSpawning(characterReference->amountToSpawnPerSpawner);

	// Invulnerable-mode must be active for this time in case it takes time for the units to spawn.
	// This is so the boss won't immediately switch back to active mode.
	constexpr float minimumInvulnerableTime = 1.f;
	GetWorld()->GetTimerManager().SetTimer(invulnerableTimerHandle, minimumInvulnerableTime, false);
}

void ABossAIController::Invulnerable()
{
	if (!GetWorld()->GetTimerManager().IsTimerActive(invulnerableTimerHandle))
	{
		// If there player has killed all units spawned by the Minionspawners, switch mode.
		if (spawnedEnemies.Num() <= 0)
		{
			StartActiveMode();
			return;
		}

		// The actor is being destroyed, it is considered dead and is removed from the actor-array.
		for (auto enemy : spawnedEnemies)
		{
			if (enemy->IsActorBeingDestroyed() == true)
				spawnedEnemies.RemoveSingleSwap(enemy);
		}
	}
}