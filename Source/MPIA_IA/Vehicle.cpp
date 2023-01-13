// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle.h"

#include "Engine/TargetPoint.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AVehicle::AVehicle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MaxSpeed = 1.f;
	MaxForce = 5.f;
	Point = FVector(270.f,-320.f,0.f); 
}

void AVehicle::UpdatePosition()
{
	float SteeringForce = 1.f;
	float Acceleration = SteeringForce / Mass;
	Position += Velocity; 
}

void AVehicle::UpdateOrientation()
{
	UKismetMathLibrary::Vector_Normalize(Velocity);
	FVector ApproximateUp = FVector(0.f, 0.f, 0.f); 
	FVector NewSide = FVector::CrossProduct(Velocity, ApproximateUp); 
	FVector NewUp = FVector::CrossProduct(Velocity, NewSide);
	Orientation = FMatrix(Velocity, ApproximateUp, NewSide, NewUp); 
}

FVector AVehicle::Seek()
{
	FVector DesiredVelocity = UKismetMathLibrary::Subtract_VectorVector(Point, GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation()); 
	UKismetMathLibrary::Vector_Normalize(DesiredVelocity, MaxSpeed); 
	//GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(UKismetMathLibrary::Subtract_VectorVector(DesiredVelocity, GetVelocity()));
	UE_LOG(LogTemp, Warning, TEXT("%s"), *DesiredVelocity.ToString());
	return UKismetMathLibrary::Subtract_VectorVector(DesiredVelocity, Velocity); 
}

FVector AVehicle::Flee()
{
	return -Seek(); 
}

// Called when the game starts or when spawned
void AVehicle::BeginPlay()
{
	Super::BeginPlay();
	
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AVehicle::Seek, 1.0, true); 
	
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

