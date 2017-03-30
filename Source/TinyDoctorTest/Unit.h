// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Unit.generated.h"

UCLASS()
class TINYDOCTORTEST_API AUnit : public ACharacter
{
	GENERATED_BODY()

protected:
	// Sets default values for this character's properties
	AUnit();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float health = 3.f;

	UPROPERTY(BlueprintReadOnly)
		float maxHealth;

	// Unit takes damage and gets knocked back. Returns true if unit died.
	UFUNCTION(BlueprintCallable)
		virtual bool TakeDamageWithKnockback(float amount, FVector damageOrigin, float horizontalKnockback = 1000.f, float verticalKnockback = 1000.f);

	// Lowers unit's health. Return true if unit died.
	UFUNCTION(BlueprintCallable)
		virtual bool ReduceHealth(float amount);
	
};
