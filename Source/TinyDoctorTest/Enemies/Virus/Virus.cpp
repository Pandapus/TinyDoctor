// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "Virus.h"

#include "VirusAIController.h"

// Called when the game starts or when spawned
void AVirus::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVirus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AVirus::TakeDamageWithKnockback(const float amount, const FVector damageOrigin, const float horizontalKnockback, const float verticalKnockback)
{
	Destroy();
	return true;
}

void AVirus::Destroyed()
{
	AVirusAIController* controllerRef = Cast<AVirusAIController>(GetController());
	if (controllerRef != nullptr)
		controllerRef->RemoveSelfFromSpawnerArray();

	Super::Destroyed();
}


