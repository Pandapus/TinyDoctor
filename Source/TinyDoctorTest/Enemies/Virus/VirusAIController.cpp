// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "VirusAIController.h"

#include "VirusSpawner.h"

void AVirusAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AVirusAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AI();
}

void AVirusAIController::SetCharacterReference()
{
	Super::SetCharacterReference();
	if (Super::characterReference != nullptr)
	{
		characterReference = Cast<AVirus>(Super::characterReference);
	}
}

void AVirusAIController::RemoveSelfFromSpawnerArray()
{
	if (spawnerReference != nullptr)
		spawnerReference->RemoveItemFromArray(this);
}

void AVirusAIController::AI()
{
	switch (aiMode)
	{
		case AIMode::Wait:
			WaitMode();
			break;
		case AIMode::Chase:
			ChaseMode();
			break;
	}
}

void AVirusAIController::WaitMode()
{
	if (DistanceToPlayer() <= characterReference->detectionRadius)
	{
		spawnerReference->ChasePlayer();
	}
}

void AVirusAIController::StartChaseMode()
{
	aiMode = AIMode::Chase;
	MoveToPlayer();
}

void AVirusAIController::ChaseMode()
{
	// Manually move towards player when within distance.
	// This stops the unit from stopping before hitting the player.
	constexpr float manualMovementDistanceThreshold = 200.f;
	if (DistanceToPlayer() <= manualMovementDistanceThreshold)
		characterReference->AddMovementInput(GetVectorToPlayer());

	if (DistanceToPlayer() <= characterReference->jumpDistanceThreshold && characterReference->GetCharacterMovement()->IsMovingOnGround())
	{
		FVector direction = GetVectorToPlayer();
		direction.Z = 0.f;
		direction.Normalize();

		direction.X *= characterReference->horizontalJumpStrength;
		direction.Y *= characterReference->horizontalJumpStrength;
		direction.Z = characterReference->verticalJumpStrength;

		StopMovement();
		characterReference->LaunchCharacter(direction, true, true);
	}
		
}


