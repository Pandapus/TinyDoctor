// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "AmoebaAIController.h"

// Original MaxWalkSpeed of the character being controlled
	float walkSpeed;
// Run Speed set in the AAmoeba-actor
	float runSpeed;

	FVector roamingTargetLocation = FVector::ZeroVector;

AAmoebaAIController::AAmoebaAIController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AAmoebaAIController::BeginPlay()
{
	Super::BeginPlay();

	// CharacterReference is not nullptr if the enemy was placed by Editor.
	// In other words, runs only if placed by Editor.
	if (characterReference != nullptr)
	{
		StartPatrolMode();
	}
}

void AAmoebaAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAmoebaAIController::SetCharacterReference()
{
	Super::SetCharacterReference();
	if (Super::characterReference != nullptr)
	{
		characterReference = Cast<AAmoeba>(Super::characterReference);
		walkSpeed = characterReference->GetCharacterMovement()->MaxWalkSpeed;
		runSpeed = characterReference->runSpeed;
	}
}

void AAmoebaAIController::StartPatrolMode()
{	
	aiMode = AIMode::Patrol;
	characterReference->GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	PickNewRoamingTargetAndMoveThere();
}

void AAmoebaAIController::PatrolMode()
{
	if (CanEnemySeePlayer())
	{
		StartChaseMode();
		return;
	}

	// If the player gets too close, the enemy will start Chase Mode. Regardless of vision.
	if (DistanceToPlayer() <= characterReference->hearingRadius)
	{
		StartChaseMode();
		return;
	}

	Roaming();
}

bool AAmoebaAIController::CanEnemySeePlayer()
{
	// Checks distance to player.
	if (DistanceToPlayer() <= characterReference->detectionRadius)
	{
		// Checks if player is within field of view

		// Relative vector between player and enemy
		FVector relativeVector = GetVectorToPlayer();
		relativeVector.Z = 0.f;

		// Calculates the difference in degrees between the enemy's forward vector and relativeVector using Dot Product (Skalar)
		float dotProduct = FVector::DotProduct(characterReference->GetActorForwardVector(), relativeVector);
		float cosineValue = dotProduct / relativeVector.Size();
		float degreeDifference = FMath::Abs(FMath::RadiansToDegrees(FMath::Acos(cosineValue)));
		if (degreeDifference <= characterReference->fieldOfView / 2.f)
		{
			// Line-traces to see if we have clear line of sight to the player.
			FHitResult hitResult;
			const FVector lineTraceStart = characterReference->GetActorLocation();
			const FVector lineTraceEnd = playerReference->GetActorLocation();
			FCollisionQueryParams collisionParams = FCollisionQueryParams();
			collisionParams.AddIgnoredActor(characterReference);

			//DrawDebugLine(GetWorld(), lineTraceStart, lineTraceEnd, FColor(255, 0, 0, 255), true, 1.f, 99, 5.f);

			GetWorld()->LineTraceSingleByChannel(hitResult, lineTraceStart, lineTraceEnd, ECC_Visibility, collisionParams);
			if (hitResult.Actor == playerReference)
			{
				return true;
			}
		}
	}
	return false;
}

void AAmoebaAIController::Roaming()
{
	// Checks if the enemy is currently waiting before moving to a new point.
	if (!GetWorldTimerManager().IsTimerActive(waitingTimerHandle))
	{
		// Controls how far away the enemy must be from its targetLocation before it starts the waiting-timer.
		// NB! Be careful lowering this, might stop roaming from working
		constexpr float reachedTargetThreshold = 250.f;

		FVector vectorToTarget = FVector(roamingTargetLocation - characterReference->GetActorLocation());
		vectorToTarget.Z = 0.f;

		float distanceToTarget = vectorToTarget.Size();
		if (distanceToTarget <= reachedTargetThreshold)
		{
			GetWorldTimerManager().ClearTimer(intervalCallSafetyTimerHandle);

			constexpr float minTimerLength = 0.5f;
			constexpr float maxTimerLength = 2.f;
			float waitingLength = FMath::FRandRange(minTimerLength, maxTimerLength);

			// Waits and picks new roaming target.
			GetWorldTimerManager().SetTimer(waitingTimerHandle, this, &AAmoebaAIController::PickNewRoamingTargetAndMoveThere, waitingLength, false);
		}
	}
}

void AAmoebaAIController::PickNewRoamingTargetAndMoveThere()
{
	FNavLocation targetPointOnNavMesh;
	GetWorld()->GetNavigationSystem()->GetRandomReachablePointInRadius(originalPosition, characterReference->patrolRadius, targetPointOnNavMesh);
	roamingTargetLocation = targetPointOnNavMesh.Location;

	GetWorld()->GetNavigationSystem()->SimpleMoveToLocation(this, roamingTargetLocation);

	// Picks a new Roaming Target every x amount of seconds in case the path of our character is obscured, rendering us unable to reach our target destination.
	constexpr float maximumWalkTime = 5.f;
	GetWorldTimerManager().SetTimer(intervalCallSafetyTimerHandle, this, &AAmoebaAIController::PickNewRoamingTargetAndMoveThere, maximumWalkTime, true);
}

void AAmoebaAIController::StartChaseMode()
{
	// Chase Mode must last for x seconds before checking to enter another mode. 
	// This is to acommodate for the enemy entering Chase Mode when taking damage and not immdiately going back to Patrol Mode.
	constexpr float minChaseModeDuration = 5.f;
	GetWorldTimerManager().SetTimer(waitingTimerHandle, minChaseModeDuration, false);

	aiMode = AIMode::Chase;
	characterReference->GetCharacterMovement()->MaxWalkSpeed = runSpeed;

	MoveToPlayer();

	// Calls MoveToPlayer() every x seconds in case the last MoveTo-command stops working.
	constexpr float callMoveToPlayerInterval = 3.f;
	GetWorldTimerManager().SetTimer(intervalCallSafetyTimerHandle, this, &AAmoebaAIController::MoveToPlayer, callMoveToPlayerInterval, true);
}

void AAmoebaAIController::ChaseMode()
{
	/*
	// Check whether to start Patrol Mode.
	// The timer makes sure the ChaseMode has lasted x amount of seconds minimum.
	if (!GetWorldTimerManager().IsTimerActive(delayTimerHandle) && DistanceToPlayer() > characterReference->detectionRadius)
	{
		StartPatrolMode();
		return;
	}
	*/

	// When close enough to the player, the enemy will move manually in order not to stop in front of the player.
	constexpr float manualMovementThreshold = 200.f;
	if (DistanceToPlayer() <= manualMovementThreshold)
	{
		characterReference->AddMovementInput(GetVectorToPlayer());
	}

	if (DistanceToPlayer() <= characterReference->hitRange)
	{
		GetWorldTimerManager().ClearTimer(intervalCallSafetyTimerHandle);
		StopMovement();
		characterReference->Hit(playerReference);
	}
}