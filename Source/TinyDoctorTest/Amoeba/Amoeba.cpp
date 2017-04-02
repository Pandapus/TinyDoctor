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

	// In case the actor is spawned at runtime. The controller will then be spawned first and unable to get it's characterReference
	// using BeginPlay.
	Cast<AAmoebaAIController>(GetController())->SetCharacterReference();
}

void AAmoeba::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AAmoeba::TakeDamageWithKnockback(const float amount, const FVector damageOrigin, const float horizontalKnockback, const float verticalKnockback)
{
	if (Super::TakeDamageWithKnockback(amount, damageOrigin, horizontalKnockback, verticalKnockback) == false)
	{
		Cast<AAmoebaAIController>(GetController())->StartChaseMode();
		return false;
	}
	else
		return true;
}


