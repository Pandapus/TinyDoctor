// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unit.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
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

	USpringArmComponent* springArm;
	UCameraComponent* camera;

	void MoveForward(float value);
	void MoveRight(float value);

	UPROPERTY(BlueprintReadWrite)
		bool bStandardWeaponActive = true;

	UFUNCTION(BlueprintNativeEvent)
		void Shoot();

	UFUNCTION(BlueprintCallable)
		void ShootStandard();

	virtual void ReduceHealth(float amount, AActor* damageCauser, float horizontalKnockback, float verticalKnockback) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AProjectile> projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int ammo = 40;

	UPROPERTY(BlueprintReadOnly)
		int maxAmmo;

	UPROPERTY(EditAnywhere, Category = "Stats")
		float weaponCooldown = 0.2f;
};
