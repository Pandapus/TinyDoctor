// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "BaseAIController.h"

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();

	playerReference = Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn());
	characterReference = GetCharacter();

	originalPosition = characterReference->GetActorLocation();
}

void ABaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ABaseAIController::DistanceToPlayer()
{
	return FVector(playerReference->GetActorLocation() - characterReference->GetActorLocation()).Size();
}

void ABaseAIController::MoveToPlayer()
{
	GetWorld()->GetNavigationSystem()->SimpleMoveToActor(this, playerReference);
}
