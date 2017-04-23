// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "BaseAIController.h"

// Defines the static pointer. (Assigns the memory adress).
AActor* ABaseAIController::playerReference;

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
	
	playerReference = Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn());

	SetCharacterReference();
}

void ABaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AI();
}

void ABaseAIController::SetCharacterReference()
{
	if (characterReference == nullptr)
	{
		characterReference = Cast<AUnit>(GetCharacter());
		if (characterReference != nullptr)
			originalPosition = characterReference->GetActorLocation();
	}
}

void ABaseAIController::AI()
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

void ABaseAIController::PatrolMode() {}

void ABaseAIController::ChaseMode() {}

const FVector ABaseAIController::GetVectorToPlayer()
{
	return FVector(playerReference->GetActorLocation() - characterReference->GetActorLocation());
}

const float ABaseAIController::DistanceToPlayer()
{
	return GetVectorToPlayer().Size();
}

void ABaseAIController::MoveToPlayer()
{
	GetWorld()->GetNavigationSystem()->SimpleMoveToActor(this, playerReference);
}
