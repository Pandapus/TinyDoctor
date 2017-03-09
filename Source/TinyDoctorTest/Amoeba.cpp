// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "Amoeba.h"

#include "AmoebaAIController.h"

AAmoeba::AAmoeba()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

void AAmoeba::BeginPlay()
{
	Super::BeginPlay();

	delayed = false;
}

void AAmoeba::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAmoeba::ReduceHealth(float amount, AActor* damageCauser, float horizontalKnockback, float verticalKnockback)
{
	health -= amount;

	// If the unit is has too little health, kill it (with fire!!!)
	if (health <= 0.f)
	{
		Destroy();
		return;
	}

	FVector pushVector = FVector(GetActorLocation() - damageCauser->GetActorLocation());
	pushVector.Z = 0.f;
	pushVector.Normalize();
	pushVector.X = 0.f;
	pushVector.Y = 0.f;
	pushVector.Z = verticalKnockback;
	LaunchCharacter(pushVector, false, true);
	
	Cast<AAmoebaAIController>(GetController())->StartChaseMode();
}

