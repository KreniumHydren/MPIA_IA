// Fill out your copyright notice in the Description page of Project Settings.

#include "VehicleController.h"

// Sets default values
AVehicleController::AVehicleController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AVehicleController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVehicleController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!MovementDirection.IsZero())
	{
		const FVector NewLocation = GetActorLocation() + (MovementDirection * DeltaTime);
		SetActorLocation(NewLocation); 
	}
}

// Called to bind functionality to input
void AVehicleController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis(TEXT("MoveForward"), this, &AVehicleController::MoveForward); 
	InputComponent->BindAxis(TEXT("MoveRight"), this, &AVehicleController::MoveRight);
}

void AVehicleController::MoveForward(float Value)
{
	MovementDirection.X = FMath::Clamp(Value, -1.f, 1.f) * LengthInput;
}

void AVehicleController::MoveRight(float Value)
{
	MovementDirection.Y = FMath::Clamp(Value, -1.f, 1.f) * LengthInput;
}
