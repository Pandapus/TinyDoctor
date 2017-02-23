// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "Unit.h"


// Sets default values
AUnit::AUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();

	maxHealth = health;
	
}

// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AUnit::GetHealth(AUnit* unit)
{
	return unit->health;
}

float AUnit::GetHealthInPercent(AUnit* unit)
{
	return unit->health / unit->maxHealth;
}

void AUnit::ReduceHealth(AUnit* unit, float amount)
{
	unit->health -= amount;

	// If the unit is has too little health, kill it (with fire)
	if (unit->health <= 0.f)
		unit->Destroy();
}

void AUnit::ReduceHealth(float amount)
{
	health -= amount;

	if (health <= 0.f)
		Destroy();
}

