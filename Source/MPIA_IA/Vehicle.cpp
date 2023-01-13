// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle.h"

#include "Engine/TargetPoint.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AVehicle::AVehicle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

FVector3d AVehicle::Seek()
{
	FVector DesiredVelocity = UKismetMathLibrary::Subtract_VectorVector(Point, GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation()); 
	UKismetMathLibrary::Vector_Normalize(DesiredVelocity, MaxSpeed); 
	return UKismetMathLibrary::Subtract_VectorVector(DesiredVelocity, GetVelocity()); 
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

// Called to bind functionality to input
void AVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

