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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float runSpeed = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		float detectionRadius = 1500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		float hearingRadius = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		float fieldOfView = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		float patrolRadius = 750.f;

	UPROPERTY(BlueprintReadWrite)
		bool delayed;

	virtual void ReduceHealth(float amount, AActor* damageCauser, float horizontalKnockback, float verticalKnockback) override;
};
