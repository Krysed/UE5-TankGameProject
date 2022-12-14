// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupItem.generated.h"

UCLASS()
class TANKGAME_API APickupItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupItem();

	UPROPERTY(EditAnywhere, Category = "Components")
		class USphereComponent* SphereCollision;
	
	//Rotation movement Component
	UPROPERTY(EditAnywhere, Category = "Components")
		class URotatingMovementComponent* RotationComponent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
