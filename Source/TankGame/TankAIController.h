// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaSeconds) override;
private:
	UPROPERTY(EditAnywhere)
		class UBehaviorTree* AIBehavior;
protected:
	virtual void BeginPlay() override;
};
