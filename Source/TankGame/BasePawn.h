// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TANKGAME_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

private:
	/**
	 * Setting Up Components trough C++ side
	*/
	UPROPERTY(VisibleAnywhere, Category = "Components")
		class UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
		USceneComponent* ProjectileSpawnPoint;

protected:
	void TurretRotation(FVector LookAtTarget);

	void Fire();
};
