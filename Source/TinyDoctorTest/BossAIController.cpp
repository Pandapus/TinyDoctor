// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "BossAIController.h"

void ABossAIController::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> spawnerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMinionSpawner::StaticClass(), spawnerActors);
	for (AActor* actor : spawnerActors)
	{
		AMinionSpawner* minionSpawner = Cast<AMinionSpawner>(actor);
		spawners.Add(minionSpawner);
		minionSpawner->bossActorReference = this;
	}

	Activate();
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
	UE_LOG(LogTemp, Warning, TEXT("Boss: Activating"));

	currentHealthStep = numberOfHealthSteps;

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
	UE_LOG(LogTemp, Warning, TEXT("Boss: Active Starting"));

	aiMode = AIMode::Active;
	characterReference->bInvulnerable = false;
	currentHealthStep--;
}

void ABossAIController::Active()
{
	const float targetHealth = (characterReference->GetMaxHealth() / numberOfHealthSteps) * (currentHealthStep);
	UE_LOG(LogTemp, Warning, TEXT("Boss: TargetHealth is: %f"), targetHealth);
	if (characterReference->GetHealth() <= targetHealth)
	{
		StartInvulnerableMode();
	}
}

FTimerHandle invulnerableTimerHandle;
void ABossAIController::StartInvulnerableMode()
{
	UE_LOG(LogTemp, Warning, TEXT("Boss: Invulnerable Starting"));

	aiMode = AIMode::Invulnerable;
	characterReference->bInvulnerable = true;

	for (AMinionSpawner* minionSpawner : spawners)
	{
		minionSpawner->StartSpawning(amountToSpawnPerSpawner);
	}

	constexpr float minimumInvulnerableTime = 5.f;
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

		for (int i = 0; i < spawnedEnemies.Num(); i++)
		{
			if (spawnedEnemies[i]->IsActorBeingDestroyed() == true) spawnedEnemies.RemoveSingleSwap(spawnedEnemies[i]);
			UE_LOG(LogTemp, Warning, TEXT("Boss: Found actor being destroyed. Removing."));
		}
		UE_LOG(LogTemp, Warning, TEXT("Boss: Number of enemies active: %d"), spawnedEnemies.Num());
	}
}