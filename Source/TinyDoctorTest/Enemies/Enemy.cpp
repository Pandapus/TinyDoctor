// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "Enemy.h"

#include "BaseAIController.h"

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	// In case the actor is spawned at runtime. The controller will then be spawned first and unable to get it's characterReference
	// using BeginPlay.
	ABaseAIController* controllerReference = Cast<ABaseAIController>(GetController());
	if (controllerReference != nullptr)
		controllerReference->SetCharacterReference();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

