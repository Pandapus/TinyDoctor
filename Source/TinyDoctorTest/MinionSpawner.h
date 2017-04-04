// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MinionSpawner.generated.h"

UCLASS()
class TINYDOCTORTEST_API AMinionSpawner : public AActor
{
	GENERATED_BODY()
	
protected:
	// Sets default values for this actor's properties
	AMinionSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
		AActor* bossActorReference;

	UFUNCTION(BlueprintNativeEvent)
		void StartSpawning(const int amountToSpawn);
	
public:
	friend class ABossAIController;
};
