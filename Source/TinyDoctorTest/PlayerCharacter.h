// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectile.h"

#include "Unit.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class TINYDOCTORTEST_API APlayerCharacter : public AUnit
{
	GENERATED_BODY()

protected:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frames
	virtual void Tick(float DeltaTime) override;

public:	
	
	void MoveX(float value);
	void MoveY(float value);
	void Shoot();

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AProjectile> projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int ammo = 40;

	UPROPERTY(BlueprintReadOnly)
		int maxAmmo;
};
