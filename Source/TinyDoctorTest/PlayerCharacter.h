// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unit.h"
#include "PlayerCharacter.generated.h"

/*
 * 
 */
UCLASS()
class TINYDOCTORTEST_API APlayerCharacter : public AUnit
{
	GENERATED_BODY()
	
private:
	USpringArmComponent* springArm;

	// Stats
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		int ammo = 40;
	int maxAmmo;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		int rifleCost = 1;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		float rifleCooldown = 0.1f;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		int shotgunCost = 2;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		float shotgunCooldown = 0.3f;

	UPROPERTY(EditDefaultsOnly, Category = "Required Variables")
		TSubclassOf<class AProjectile> projectileToShoot;

	bool bRifleActive = true;
	void Shoot();
	void ShootRifle();
	
	void MoveForward(const float value);
	void MoveRight(const float value);

	void SetInvulnerableToFalse();

protected:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
		float shotgunDamage = 1.f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frames
	virtual void Tick(float DeltaTime) override;
	
	// Calls upon Blueprint-version of the shotgun.
	UFUNCTION(BlueprintNativeEvent)
		void ShootShotgun();

public:
	virtual bool ChangeHealth(const float amount) override;
	virtual bool TakeDamageWithKnockback(const float amount, const FVector damageOrigin,
										 const float horizontalKnockback, const float verticalKnockback) override;

	// Calls upon Blueprint version. This sends information to the HUD that the weapon has been changed.
	UFUNCTION(BlueprintNativeEvent)
		void WeaponChangeEvent();

	UFUNCTION(BlueprintPure)
		const int GetAmmo();
	UFUNCTION(BlueprintPure)
		const int GetMaxAmmo();
	UFUNCTION(BlueprintCallable)
		int ChangeAmmo(const int amount);
	UFUNCTION(BlueprintCallable)
		int DecreaseAmmo(const int amount);
	UFUNCTION(BlueprintPure)
		const bool IsRifleActive();

	friend class APlayerCharacterController;
};
