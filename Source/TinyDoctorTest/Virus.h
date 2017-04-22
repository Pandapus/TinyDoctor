// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy.h"
#include "Virus.generated.h"

/**
 * 
 */
UCLASS()
class TINYDOCTORTEST_API AVirus : public AEnemy
{
	GENERATED_BODY()
	
private:
	virtual bool TakeDamageWithKnockback(const float amount, const FVector damageOrigin, const float horizontalKnockback, const float verticalKnockback) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Important to call this function after having spawned the AVirus-actor.
	void Constructor(AActor* virusSpawner);

	void StartChasing();

	UPROPERTY(BlueprintReadWrite)
		bool bChasingPlayer = false;
};
