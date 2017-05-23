// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "BaseAIController.h"

// Assigns memory for the static pointer.
AActor* ABaseAIController::playerReference;

ABaseAIController::ABaseAIController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
	
	playerReference = Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn());

	SetCharacterReference();
}

void ABaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
