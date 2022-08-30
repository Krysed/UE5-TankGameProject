// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	/**
	 * Attaching Tank Base Mesh to Capsule component
	*/
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	/**
	 * Attaching Tank Turret Mesh to base Mesh
	*/
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	/**
	 * Attaching ProjectileSpawn Point to Turret Mesh
	*/
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}
/**
 * @brief Handling Turret rotation
 * @param LookAtTarget = location of mouse coursor
*/
void ABasePawn::TurretRotation(FVector LookAtTarget)
{
	FVector ToTargetVector = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(
		0.f,							//Pitch
		ToTargetVector.Rotation().Yaw,	//Yaw
		0.f								//Roll	
	);

	//Rotating Turret
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			10.f
		)
	);
}

void ABasePawn::Fire()
{
	//Geting Location and rotation of spawn point to spawn projectile facing the right direction
	FVector ProjectileLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator ProjectileRotation = ProjectileSpawnPoint->GetComponentRotation();

	//Spawning A projectile
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileLocation, ProjectileRotation);
	Projectile->SetOwner(this);
}