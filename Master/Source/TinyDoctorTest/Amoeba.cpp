// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "Amoeba.h"

AAmoeba::AAmoeba()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AAmoeba::BeginPlay()
{
	Super::BeginPlay();
}

void AAmoeba::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



