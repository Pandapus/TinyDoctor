// Fill out your copyright notice in the Description page of Project Settings.

#include "TinyDoctorTest.h"
#include "StandardGameMode.h"

void AStandardGameMode::PauseGame_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Pause Game-method is not intended to be used in C++. Use a BP version of this method."));
}

void AStandardGameMode::GameOver_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Over-method is not intended to be used in C++. Use a BP version of this method."));
}
