// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectile.h"

#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class TINYDOCTORTEST_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frames
	virtual void Tick(float DeltaTime) override;

	void MoveX(float value);
	void MoveY(float value);
	void Shoot();

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AProjectile> projectile;
};
