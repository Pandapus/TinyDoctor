// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "AmoebaAIController.h"

void AAmoebaAIController::BeginPlay()
{
	Super::BeginPlay();

	playerReference = Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	characterReference = Cast<AAmoeba>(GetPawn());

	originalPosition = characterReference->GetActorLocation();

	walkSpeed = characterReference->GetCharacterMovement()->MaxWalkSpeed;

	StartPatrolMode();
}

void AAmoebaAIController::Tick(float DeltaTime)
{
	if (!characterReference->delayed)
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
	// Checks distance to player to see whether to start chasing him or not.
	if (DistanceToPlayer() <= characterReference->detectionRadius)
	{
		// Checks if player is within field of view

		// Relative vector between player and enemy
		FVector relativeVector = FVector(playerReference->GetActorLocation() - characterReference->GetActorLocation());

		// Calculates the difference in degrees between the enemy's forward vector and relativeVector
		float dotProduct = FVector::DotProduct(characterReference->GetActorForwardVector(), relativeVector);
		float cosineValue = dotProduct / relativeVector.Size();
		float degreeDifference = FMath::Abs(FMath::RadiansToDegrees(FMath::Acos(cosineValue)));
		if (degreeDifference <= characterReference->fieldOfView / 2.f)
		{
			// Insert line-tracing code here
			FHitResult hitResult;
			const FVector lineTraceStart = characterReference->GetActorLocation();
			const FVector lineTraceEnd = playerReference->GetActorLocation();
			FCollisionQueryParams collisionParams = FCollisionQueryParams();
			collisionParams.AddIgnoredActor(characterReference);

			//DrawDebugLine(GetWorld(), lineTraceStart, lineTraceEnd, FColor(255, 0, 0, 255), true, 1.f, 99, 5.f);

			GetWorld()->LineTraceSingleByChannel(hitResult, lineTraceStart, lineTraceEnd, ECC_Visibility, collisionParams);
			if (hitResult.Actor == playerReference)
			{
				StartChaseMode();
				return;
			}
		}
	}

	// If the player gets too close, the enemy will start Chase Mode. Regardless of vision.
	if (DistanceToPlayer() <= characterReference->hearingRadius)
	{
		StartChaseMode();
		return;
	}

	Roaming();
}

void AAmoebaAIController::Roaming()
{
	if (!GetWorldTimerManager().IsTimerActive(delayTimerHandle))
	{
		// Controls how far away the enemy must be from its target before it starts the waiting-timer.
		// NB! Be careful changing this, might stop roaming from working
		const float reachedTargetThreshold = 150.f;
		
		float distanceToTarget = FVector(targetPosition - characterReference->GetActorLocation()).Size();
		if (distanceToTarget <= reachedTargetThreshold)
		{
			const float minTimerLength = 0.5f;
			const float maxTimerLength = 2.f;
			float timerLength = FMath::FRandRange(minTimerLength, maxTimerLength);
			GetWorldTimerManager().SetTimer(delayTimerHandle, this, &AAmoebaAIController::PickNewRoamingTargetAndMoveThere, timerLength, false);
		}
	}
}

void AAmoebaAIController::PickNewRoamingTargetAndMoveThere()
{
	FNavLocation targetPointOnNavMesh;
	GetWorld()->GetNavigationSystem()->GetRandomReachablePointInRadius(originalPosition, characterReference->patrolRadius, targetPointOnNavMesh);
	targetPosition = targetPointOnNavMesh.Location;

	GetWorld()->GetNavigationSystem()->SimpleMoveToLocation(this, targetPosition);
}

void AAmoebaAIController::ChaseMode()
{
	// Check whether to start Patrol Mode. 
	if (!GetWorldTimerManager().IsTimerActive(delayTimerHandle) && DistanceToPlayer() > characterReference->detectionRadius)
	{
		StartPatrolMode();
		return;
	}

	// When close enough to the player, the enemy will move manually in order not to stop in front of the player.
	const float manualMovementThreshold = 200.f;
	if (DistanceToPlayer() <= manualMovementThreshold)
	{
		characterReference->AddMovementInput(FVector(playerReference->GetActorLocation() - characterReference->GetActorLocation()));
	}
}

void AAmoebaAIController::StartChaseMode()
{
	// Chase Mode must last for x seconds before checking to enter another mode. 
	// This is to acommodate for the enemy entering Chase Mode when taking damage and not immdiately going back to Patrol Mode.
	GetWorldTimerManager().SetTimer(delayTimerHandle, 3.0f, false);

	aiMode = AIMode::Chase;
	characterReference->GetCharacterMovement()->MaxWalkSpeed = characterReference->runSpeed;
	MoveToPlayer();
}

void AAmoebaAIController::MoveToPlayer()
{
	GetWorld()->GetNavigationSystem()->SimpleMoveToActor(this, playerReference);
}

float AAmoebaAIController::DistanceToPlayer()
{
	return FVector(playerReference->GetActorLocation() - characterReference->GetActorLocation()).Size();
}

