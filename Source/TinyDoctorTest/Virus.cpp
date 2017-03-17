// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "Virus.h"

#include "VirusSpawner.h"
#include "BaseAIController.h"

AVirusSpawner* virusSpawner;

// Called when the game starts or when spawned
void AVirus::BeginPlay()
{
	Super::BeginPlay();

	ABaseAIController* controller = Cast<ABaseAIController>(GetController());
	controller->characterReference = this;
	controller->originalPosition = GetActorLocation();
}

// Called every frame
void AVirus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVirus::Constructor(AActor* virusSpawnerRef)
{
	virusSpawner = Cast<AVirusSpawner>(virusSpawnerRef);
	virusSpawner->AddActorToArray(this);
}

void AVirus::StartChasing()
{
	virusSpawner->ChasePlayer();
}

void AVirus::ReduceHealth(float amount, AActor* damageCauser, float horizontalKnockback, float verticalKnockback)
{
	health -= amount;

	// If the unit is has too little health, kill it (with fire!!!)
	if (health <= 0.f)
	{
		virusSpawner->RemoveActorFromArray(this);
		Destroy();
		return;
	}

	FVector pushVector = FVector(0.f, 0.f, verticalKnockback);
	LaunchCharacter(pushVector, false, true);
}



