// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "StandardGameMode.h"

AStandardGameMode::AStandardGameMode()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AStandardGameMode::PauseGame_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("AStandardGameMode::PauseGame() is not intended to be used in C++. Use a BP version of this method."));
}

void AStandardGameMode::GameOver_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("AStandardGameMode::GameOver() is not intended to be used in C++. Use a BP version of this method."));
}

void AStandardGameMode::GameWon_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("AStandardGameMode::GameWon() is not intended to be used in C++. Use a BP version of this method."));
}
