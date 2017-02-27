// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unit.h"
#include "Amoeba.generated.h"

/**
 * 
 */
UCLASS()
class TINYDOCTORTEST_API AAmoeba : public AUnit
{
	GENERATED_BODY()
	
protected:
	// Constructor
	AAmoeba();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	
	UPROPERTY(EditAnywhere, Category = "Stats")
		float slowWalkSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "AI")
		float detectionRange = 1500.f;

	UPROPERTY(EditAnywhere, Category = "AI")
		float patrolRadius = 750.f;

	UPROPERTY(BlueprintReadWrite)
		bool delayed;

	
};
