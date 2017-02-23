// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Unit.generated.h"

UCLASS()
class TINYDOCTORTEST_API AUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float health = 5.f;

	float maxHealth;

	UFUNCTION(BlueprintCallable)
		static float GetHealth(AUnit* unit);

	UFUNCTION(BlueprintCallable)
		static float GetHealthInPercent(AUnit* unit);

	UFUNCTION(BlueprintCallable)
		static void ReduceHealth(AUnit* unit,float amount);

	virtual void ReduceHealth(float amount);
	
	
};
