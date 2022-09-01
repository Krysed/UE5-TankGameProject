// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"
#include "Components/StaticMeshComponent.h"


//Health Pickup Constructor Implementation
AHealthPickup::AHealthPickup()
{
	//Seting up mesh
	HeartBar1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeartBar1"));
	HeartBar1->SetupAttachment(RootComponent);
	
	HeartBar2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeartBar2"));
	HeartBar2->SetupAttachment(RootComponent);
}

/**
 * @brief Heal target when is within range
*/
void AHealthPickup::HealOnOverlap()
{
	
}