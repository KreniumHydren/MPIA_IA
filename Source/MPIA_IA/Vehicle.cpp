// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AVehicle::AVehicle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement")); 
	Movement->MaxSpeed = MaxSpeedEffective;
}

// Called when the game starts or when spawned
void AVehicle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

