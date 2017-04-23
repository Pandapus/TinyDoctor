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

void AVirusAIController::PatrolMode()
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

	constexpr float moveToPlayerCallInterval = 3.f;
	GetWorldTimerManager().SetTimer(timerMoveToPlayerManager, this, &AVirusAIController::MoveToPlayer, moveToPlayerCallInterval, true);
}

void AVirusAIController::ChaseMode()
{
	constexpr float manualMovementDistanceThreshold = 500.f;
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

		characterReference->LaunchCharacter(direction, true, true);
	}
		
}


