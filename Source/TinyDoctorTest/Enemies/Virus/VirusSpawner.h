// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VirusAIController.h"

#include "GameFramework/Actor.h"
#include "VirusSpawner.generated.h"

UCLASS()
class TINYDOCTORTEST_API AVirusSpawner : public AActor
{
	GENERATED_BODY()
	
private:
	// Sets default values for this actor's properties
	AVirusSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnVirus();

	TArray<AVirusAIController*> virusArray;
	void RemoveItemFromArray(AVirusAIController* itemToRemove);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Required variables")
		TSubclassOf<class AVirus> virusToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
		int numberToSpawn = 3;

	UFUNCTION(BlueprintCallable)
		void ChasePlayer();
	
public:
	friend class AVirusAIController;
};
