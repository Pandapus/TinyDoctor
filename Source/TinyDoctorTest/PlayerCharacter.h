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

	// Stats
	UPROPERTY(EditAnywhere, Category = "Stats")
		int ammo = 40;
	int maxAmmo;
	UPROPERTY(EditAnywhere, Category = "Stats")
		float weaponCooldown = 0.2f;

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
	UFUNCTION(BlueprintPure)
		const int GetAmmo();
	UFUNCTION(BlueprintPure)
		const int GetMaxAmmo();
	UFUNCTION(BlueprintCallable)
		int ChangeAmmo(const int amount);
	UFUNCTION(BlueprintCallable)
		int DecreaseAmmo(const int amount);

	friend class APlayerCharacterController;
};
