// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "BossAIController.h"

void ABossAIController::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> spawnerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMinionSpawner::StaticClass(), spawnerActors);
	for(AActor* actor : spawnerActors)
	{
		AMinionSpawner* minionSpawner = Cast<AMinionSpawner>(actor);
		spawners.Add(minionSpawner);
		minionSpawner->bossActorReference = this;

	}
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
}

void ABossAIController::Active()
{

}

void ABossAIController::StartInvulnerableMode()
{
	aiMode = AIMode::Invulnerable;
	characterReference->bInvulnerable = true;

	for (AMinionSpawner* minionSpawner : spawners)
	{
		minionSpawner->StartSpawning(amountToSpawnPerSpawner);
	}
}

void ABossAIController::Invulnerable()
{
	for (AActor* actor : spawnedEnemies)
	{
		if (actor == nullptr) spawnedEnemies.RemoveSwap(actor);
	}

	if (spawnedEnemies.Num() <= 0)
		StartActiveMode();
}