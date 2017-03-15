// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Virus.h"

#include "GameFramework/Actor.h"
#include "VirusSpawner.generated.h"

UCLASS()
class TINYDOCTORTEST_API AVirusSpawner : public AActor
{
	GENERATED_BODY()
	
private:
	// Sets default values for this actor's properties
	AVirusSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<AVirus*> virusArray;

	void ChasePlayer();

public:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AVirus> virus;

	UPROPERTY(EditAnywhere)
		int numberToSpawn = 3;
	
};
