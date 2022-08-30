// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

/**
 * A Tank Class Constructor Definition
*/
ATank::ATank()
{
	//Setting Up Spring Arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	//Seting Up Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}
/**
 * @brief Called at Start of the game or when spawned
*/
void ATank::BeginPlay()
{
	Super::BeginPlay();

	//Casting AController to APlayerController
	PlayerControllerReference = Cast<APlayerController>(GetController());

}
/**
 * @brief Player input handling
 * @param PlayerInputComponent = Converts player input to movement
*/
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//using Super not to miss any functionality from overriding function from parent class
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	//IE_Pressed = Called on pressing button
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

/**
 * @Move Function for Tank Pawn
 * @param Value = How fast tank will move
*/
void ATank::Move(float Value)
{
	//Seting X,Y,Z Value to 0
	FVector DeltaLocation(0.f);

	//Passing value to x, Value * DeltaTime * Speed variable 
	//Scaling it by DeltaTime for movement to be Framerate independent
	DeltaLocation.X = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed;

	AddActorLocalOffset(DeltaLocation, true);
}
void ATank::Turn(float Value)
{
	//Seting up default Rotator value
	FRotator DeltaRotation(0.f);

	//Rotation around Z axis
	DeltaRotation.Yaw = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate;

	/**
	 * @brief = Adding Rotation to a Tank Pawn
	*/
	AddActorLocalRotation(DeltaRotation, true);
}
/**
 * @brief Called every frame
*/
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Checking if PlayerControllerREference is valid(!= nullptr)
	if (PlayerControllerReference)
	{
		FHitResult HitResult;
		PlayerControllerReference->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult);

		TurretRotation(HitResult.ImpactPoint);
	}
}
