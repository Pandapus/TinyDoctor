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

	UPROPERTY(EditAnywhere, Category = "Stats")
		float touchDamage = 1.f;

	UPROPERTY(EditAnywhere, Category = "Stats")
		float runSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "AI")
		float fieldOfView = 90.f;

	UPROPERTY(EditAnywhere, Category = "AI")
		float hearingRadius = 500.f;

	UPROPERTY(EditAnywhere, Category = "AI")
		float patrolRadius = 750.f;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	virtual bool TakeDamageWithKnockback(const float amount, const FVector damageOrigin, const float horizontalKnockback, const float verticalKnockback) override;

	UFUNCTION(BlueprintCallable)
		void StartChaseMode();

	friend class AAmoebaAIController;
};
