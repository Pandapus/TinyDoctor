// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "VirusSpawner.h"

#include "Virus.h"

// Sets default values
AVirusSpawner::AVirusSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
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
}

void AVirusSpawner::RemoveItemFromArray(AVirusAIController* const &itemToRemove)
{
	virusArray.RemoveSingleSwap(itemToRemove);
	if (virusArray.Num() <= 0)
		Destroy();
}

void AVirusSpawner::SpawnVirus()
{
	for (int i = 1; i <= numberToSpawn; i++)
	{
		const float randomYawRotation = FMath::FRandRange(-180.f, 180.f);
		const FRotator spawnDirection = FRotator(0.f, randomYawRotation, 0.f);

		FActorSpawnParameters spawnParameter = FActorSpawnParameters();
		spawnParameter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// Consider changing to automatically choose good radius depending on amount to spawn.
		constexpr float spawnRadius = 250.f;

		// Picks random location on Navmesh (within radius) to choose where to spawn.
		FNavLocation spawnLocationOnNavMesh = FNavLocation();
		GetWorld()->GetNavigationSystem()->GetRandomPointInNavigableRadius(GetActorLocation(), spawnRadius, spawnLocationOnNavMesh);
		FVector spawnLocation = spawnLocationOnNavMesh.Location;
		spawnLocation.Z += 100.f;

		FTransform actorTransform = FTransform(spawnDirection, spawnLocation);

		AVirus* virusActor = GetWorld()->SpawnActor<AVirus>(virusToSpawn, actorTransform, spawnParameter);
		if (virusActor != nullptr)
		{
			AVirusAIController* controllerRef = Cast<AVirusAIController>(virusActor->GetController());
			controllerRef->spawnerReference = this;
			virusArray.Add(controllerRef);
		}
	}
}

void AVirusSpawner::ChasePlayer()
{
	for (auto controllerRef : virusArray)
	{
		controllerRef->StartChaseMode();
	}
}