// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "Virus.h"

#include "BaseAIController.h"

// Called when the game starts or when spawned
void AVirus::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVirus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AVirus::TakeDamageWithKnockback(const float amount, const FVector damageOrigin, const float horizontalKnockback, const float verticalKnockback)
{
	Destroy();
	return true;
}

void AVirus::Constructor(AActor* virusSpawnerRef)
{
	//virusSpawner = Cast<AVirusSpawner>(virusSpawnerRef);
}

void AVirus::StartChasing()
{
	//virusSpawner->ChasePlayer();
}



