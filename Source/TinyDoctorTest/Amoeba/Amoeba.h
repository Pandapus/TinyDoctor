// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy.h"
#include "Amoeba.generated.h"

/**
 * 
 */
UCLASS()
class TINYDOCTORTEST_API AAmoeba : public AEnemy
{
	GENERATED_BODY()

protected:
	// Constructor
	AAmoeba();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
		float runSpeed = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		float hearingRadius = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		float fieldOfView = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		float patrolRadius = 750.f;

public:

	virtual bool TakeDamageWithKnockback(const float amount, const FVector damageOrigin, const float horizontalKnockback, const float verticalKnockback) override;

	friend class AAmoebaAIController;
};
