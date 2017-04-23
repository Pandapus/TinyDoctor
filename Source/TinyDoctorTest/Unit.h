// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Unit.generated.h"

UCLASS()
class TINYDOCTORTEST_API AUnit : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		float health = 3.f;
	float maxHealth;

	// Alters the unit's health. Returns true if the unit died.
	UFUNCTION(BlueprintCallable)
		bool ChangeHealth(const float amount, float &newHealth);

	// Decreases the unit's health. Returns true if the unit died.
	UFUNCTION(BlueprintCallable)
		bool DecreaseHealth(const float amount, float &newHealth);

protected:
	// Sets default values for this character's properties
	AUnit();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bInvulnerable = false;
	UFUNCTION(BlueprintPure)
		const bool IsInvulnerable();

public:
	UFUNCTION(BlueprintPure)
		const float GetHealth();

	UFUNCTION(BlueprintPure)
		const float GetMaxHealth();

	// Unit takes damage and gets knocked back. Returns true if unit died.
	UFUNCTION(BlueprintCallable)
		virtual bool TakeDamageWithKnockback(const float amount, const FVector damageOrigin, 
											 const float horizontalKnockback = 1000.f, const float verticalKnockback = 750.f);

	// Alters the unit's health. Returns true if the unit died.
	virtual bool ChangeHealth(const float amount);
	
	friend class APlayerCharacter;
};
