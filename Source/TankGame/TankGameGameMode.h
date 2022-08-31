// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API ATankGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	//forward declaring ATank variable;
	class ATank* Tank;

	//forward declaring ATankGamePlayerController variable
	class ATankGamePlayerController* TankGamePlayerController;

	float StartGameDelay = 3.f;

	void HandleGameStart();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

public:
	/**
	 * @brief Handling Death
	 * @param DeadActor = Actor that will be dead
	*/
	void ActorDead(AActor* DeadActor);
};
