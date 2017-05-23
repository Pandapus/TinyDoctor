// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemies/Enemy.h"
#include "Amoeba.generated.h"

/**
 * 
 */
UCLASS()
class TINYDOCTORTEST_API AAmoeba : public AEnemy
{
	GENERATED_BODY()

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Constructor
	AAmoeba();

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		float touchDamage = 1.f;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		float hitRange = 200.f;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		float runSpeed = 200.f;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		float fieldOfView = 90.f;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		float hearingRadius = 500.f;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		float patrolRadius = 750.f;

	// Function for when the amoeba hits the player.
	void Hit(AActor* OtherActor);

public:
	virtual bool TakeDamageWithKnockback(const float amount, const FVector damageOrigin, const float horizontalKnockback, const float verticalKnockback) override;

	UFUNCTION(BlueprintCallable)
		void StartChaseMode();

	friend class AAmoebaAIController;
};
