// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Turret.h"
#include "TankGameGameMode.h"
#include "Kismet/GameplayStatics.h"

void ATankGameGameMode::ActorDead(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (Tank->GetTankPlayerController())
		{
			Tank->DisableInput(Tank->GetTankPlayerController());
			Tank->GetTankPlayerController()->bShowMouseCursor = false;
		}
	}
	else if (ATurret* DestroyedTurret = Cast<ATurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
	}
}

void ATankGameGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Get PlayerPawn
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}