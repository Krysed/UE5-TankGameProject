// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Setting Default mesh for projectile
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	//seting default values for speed of the launched projectile
	ProjectileMovementComponent->MaxSpeed = 1700.f;
	ProjectileMovementComponent->InitialSpeed = 1700.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	//Binding Function to mesh
	ProjectileMesh->OnComponentHit.AddDynamic(this,&AProjectile::OnHitEvent);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/**
 * @brief Event that happens on Hit 
*/
void AProjectile::OnHitEvent(UPrimitiveComponent* HitComp, 
								AActor* OtherActor, 
								UPrimitiveComponent* OtherComponent,
								FVector NormalInpulse,
								const FHitResult& Hit
							)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
		
		//DamageTypeClass for ApplyDamage event
		UClass* DamageTypeClass = UDamageType::StaticClass();

		if (OtherActor && OtherActor != this && OtherActor != MyOwner)
		{
			//Generating Damage event
			UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);

			//Destroying projectile after dealing damage
			Destroy();
		}
	}
}