// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "VirusAIController.h"

#include "Virus.h"

void AVirusAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AVirusAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AI();
}

void AVirusAIController::PatrolMode()
{
	if (DistanceToPlayer() <= characterReference->detectionRadius)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player within range"));
		Cast<AVirus>(characterReference)->StartChasing();
	}
}

void AVirusAIController::ChaseMode()
{
	constexpr float closenessThreshold = 500.f;
	if (DistanceToPlayer() <= closenessThreshold && characterReference->GetCharacterMovement()->IsMovingOnGround())
	{
		characterReference->AddMovementInput(FVector(playerReference->GetActorLocation() - characterReference->GetActorLocation()));

		FVector direction = FVector(playerReference->GetActorLocation() - characterReference->GetActorLocation());
		direction.Z = 0.f;
		direction.Normalize();

		constexpr float horizontalJumpStrength = 500.f;
		direction.X *= horizontalJumpStrength;
		direction.Y *= horizontalJumpStrength;

		constexpr float verticalJumpStrength = 1000.f;
		direction.Z = verticalJumpStrength;

		characterReference->LaunchCharacter(direction, true, true);
	}
		
}


