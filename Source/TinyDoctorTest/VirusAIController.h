// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseAIController.h"
#include "VirusAIController.generated.h"

/**
 * 
 */
UCLASS()
class TINYDOCTORTEST_API AVirusAIController : public ABaseAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	virtual void PatrolMode() override;
	virtual void ChaseMode() override;

	
};
