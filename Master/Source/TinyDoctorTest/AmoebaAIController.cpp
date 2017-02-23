// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "AmoebaAIController.h"

void AAmoebaAIController::BeginPlay()
{
	Super::BeginPlay();

	if (playerReference == nullptr)
		playerReference = Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	characterReference = Cast<AAmoeba>(GetPawn());

	originalPosition = characterReference->GetActorLocation();

	bRoamingMovingToLocation = false;

	originalWalkSpeed = characterReference->GetCharacterMovement()->MaxWalkSpeed;
}

void AAmoebaAIController::Tick(float DeltaTime)
{
	AI();
}

void AAmoebaAIController::AI()
{
	switch (aiMode)
	{
	case AIMode::Patrol:
		PatrolMode();
		break;
	case AIMode::Chase:
		ChaseMode();
		break;
	case AIMode::Return:
		ReturnMode();
		break;
	}
}

void AAmoebaAIController::PatrolMode()
{
	characterReference->GetCharacterMovement()->MaxWalkSpeed = characterReference->slowWalkSpeed;

	// Check whether to start Chase Mode
	float distanceToPlayer = FVector(playerReference->GetActorLocation() - characterReference->GetActorLocation()).Size();
	if (distanceToPlayer <= characterReference->detectionRange)
	{
		bRoamingMovingToLocation = false;
		characterReference->GetCharacterMovement()->MaxWalkSpeed = originalWalkSpeed;
		aiMode = AIMode::Chase;
		GetWorld()->GetNavigationSystem()->SimpleMoveToActor(this, playerReference);
		ChaseMode();
		return;
	}

	AIRoam();
}

void AAmoebaAIController::AIRoam()
{
	if (!bRoamingMovingToLocation)
	{
		targetPosition = originalPosition;
		targetPosition.X += FMath::FRandRange(-characterReference->patrolRadius, characterReference->patrolRadius);
		targetPosition.Y += FMath::FRandRange(-characterReference->patrolRadius, characterReference->patrolRadius);

		GetWorld()->GetNavigationSystem()->SimpleMoveToLocation(this, targetPosition);
		bRoamingMovingToLocation = true;
	}
	else
	{
		const float reachedTargetThreshold = 100.f;
		float distanceToTarget = FVector(targetPosition - characterReference->GetActorLocation()).Size();
		if (distanceToTarget <= reachedTargetThreshold)
		{
			bRoamingMovingToLocation = false;
		}
	}
}

void AAmoebaAIController::ChaseMode()
{
	// Check whether to start Return Mode
	float distanceToPlayer = FVector(playerReference->GetActorLocation() - characterReference->GetActorLocation()).Size();
	if (distanceToPlayer > characterReference->detectionRange)
	{
		characterReference->GetCharacterMovement()->MaxWalkSpeed = characterReference->slowWalkSpeed;
		aiMode = AIMode::Return;
		GetWorld()->GetNavigationSystem()->SimpleMoveToLocation(this, originalPosition);
		ReturnMode();
		return;
	}
}

void AAmoebaAIController::ReturnMode()
{
	// Check whether to start Chase Mode
	float distanceToPlayer = FVector(playerReference->GetActorLocation() - characterReference->GetActorLocation()).Size();
	if (distanceToPlayer <= characterReference->detectionRange)
	{
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = originalWalkSpeed;
		aiMode = AIMode::Chase;
		GetWorld()->GetNavigationSystem()->SimpleMoveToActor(this, playerReference);
		ChaseMode();
		return;
	}
	
	// Check whether to start Patrol Mode
	const float reachedTargetThreshold = 300.f;
	float distanceToTarget = FVector(originalPosition - GetPawn()->GetActorLocation()).Size();
	if (distanceToTarget <= reachedTargetThreshold)
	{
		characterReference->GetCharacterMovement()->MaxWalkSpeed = characterReference->slowWalkSpeed;
		aiMode = AIMode::Patrol;
		PatrolMode();
		return;
	}
}

