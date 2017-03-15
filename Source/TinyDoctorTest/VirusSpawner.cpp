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
	
	for (int i = 0; i <= numberToSpawn; i++)
	{
		FActorSpawnParameters spawnParameter = FActorSpawnParameters();
		spawnParameter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		AVirus* virusActor = GetWorld()->SpawnActor<AVirus>(virus, GetActorLocation(), FRotator::ZeroRotator, spawnParameter);
		virusArray.Add(virusActor);
	}
}

// Called every frame
void AVirusSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	for (AVirus* blehVirus : virusArray)
	{
		ABaseAIController* controller = Cast<ABaseAIController>(blehVirus->GetController());
		APawn* playerReference = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (FVector(playerReference->GetActorLocation() - blehVirus->GetActorLocation()).Size() <= blehVirus->detectionRadius)
		{
			ChasePlayer();
			break;
		}
	}
}

void AVirusSpawner::ChasePlayer()
{
	APawn* playerReference = GetWorld()->GetFirstPlayerController()->GetPawn();
	for (AVirus* blehVirus : virusArray)
	{
		GetWorld()->GetNavigationSystem()->SimpleMoveToActor(blehVirus->GetController(), playerReference);
	}
}

