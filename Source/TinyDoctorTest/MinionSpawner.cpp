// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "MinionSpawner.h"

#include "BossAIController.h"

// Sets default values
AMinionSpawner::AMinionSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMinionSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMinionSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMinionSpawner::StartSpawning_Implementation(const int amountToSpawn)
{
	// Insert warning
}

