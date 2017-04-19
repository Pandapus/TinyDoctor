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
	
private:
	USpringArmComponent* springArm;

	void SetInitialStats();

	// Stats
	UPROPERTY(EditAnywhere, Category = "Stats")
		int ammo = 40;
	int maxAmmo;
	UPROPERTY(EditAnywhere, Category = "Stats")
		int singleShotCost = 1;
	UPROPERTY(EditAnywhere, Category = "Stats")
		float singleShotCooldown = 0.1f;
	UPROPERTY(EditAnywhere, Category = "Stats")
		float shotgunCooldown = 0.3f;

	// Weapon associated variables and methods.
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AProjectile> projectile;
	bool bStandardWeaponActive = true;
	void Shoot();
	void ShootStandard();
	
	void MoveForward(const float value);
	void MoveRight(const float value);

protected:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frames
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
		void Shotgun();

public:
	virtual bool ChangeHealth(const float amount) override;

	UFUNCTION(BlueprintPure)
		const int GetAmmo();
	UFUNCTION(BlueprintPure)
		const int GetMaxAmmo();
	UFUNCTION(BlueprintCallable)
		int ChangeAmmo(const int amount);
	UFUNCTION(BlueprintCallable)
		int DecreaseAmmo(const int amount);
	UFUNCTION(BlueprintPure)
		const bool GetActiveWeapon();
	UFUNCTION(BlueprintNativeEvent)
		void WeaponChangeEvent();

	friend class APlayerCharacterController;
};
