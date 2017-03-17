// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "VirusSpawner.h"

#include "BaseAIController.h"

// Sets default values
AVirusSpawner::AVirusSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AVirusSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnVirus();
}

// Called every frame
void AVirusSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	/*
	if (aiMode == AIMode::Wait)
	{
		for (AVirus* virusActor : virusArray)
		{
			ABaseAIController* controller = Cast<ABaseAIController>(virusActor->GetController());
			APawn* playerReference = GetWorld()->GetFirstPlayerController()->GetPawn();
			if (FVector(playerReference->GetActorLocation() - virusActor->GetActorLocation()).Size() <= virusActor->detectionRadius)
			{
				ChasePlayer();
				break;
			}
		}
	}
	*/
}

void AVirusSpawner::SpawnVirus()
{
	for (int i = 1; i <= numberToSpawn; i++)
	{
		const float randomYawRotation = FMath::FRandRange(-180.f, 180.f);
		const FRotator spawnDirection = FRotator(0.f, randomYawRotation, 0.f);

		FActorSpawnParameters spawnParameter = FActorSpawnParameters();
		spawnParameter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		constexpr float spawnRadius = 200.f;
		FNavLocation spawnLocationOnNavMesh = FNavLocation();
		GetWorld()->GetNavigationSystem()->GetRandomPointInNavigableRadius(GetActorLocation(), spawnRadius, spawnLocationOnNavMesh);
		FVector spawnLocation = spawnLocationOnNavMesh.Location;
		spawnLocation.Z += 100.f;

		AVirus* virusActor = GetWorld()->SpawnActor<AVirus>(virus, spawnLocation, spawnDirection, spawnParameter);
		virusActor->Constructor(this);
	}
}

void AVirusSpawner::ChasePlayer()
{
	for (AVirus* virusActor : virusArray)
	{
		ABaseAIController* controller = Cast<ABaseAIController>(virusActor->GetController());
		controller->MoveToPlayer();
		controller->aiMode = ABaseAIController::AIMode::Chase;
	}
}

void AVirusSpawner::RemoveActorFromArray(AVirus* virusActor)
{
	virusArray.Remove(virusActor);
}

void AVirusSpawner::AddActorToArray(AVirus* virusActor)
{
	virusArray.Add(virusActor);
}