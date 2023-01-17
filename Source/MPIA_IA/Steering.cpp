// Fill out your copyright notice in the Description page of Project Settings.


#include "Steering.h"

FVector Truncate(FVector Vector, float Max)
{
	return (Vector * Max) / Vector.Length();  
}

// Sets default values
ASteering::ASteering()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASteering::UpdatePosition(FVector SteeringDirection)
{
	FVector Acceleration = Truncate(SteeringDirection, AI->MaxForce)  / AI->Mass; 
	FVector VelocityTruncate = Truncate(AI->Movement->Velocity + Acceleration, AI->Movement->MaxSpeed);
	AI->Movement->Velocity = VelocityTruncate;
	AI->SetActorLocation(AI->GetActorLocation() + AI->Movement->Velocity);
}

void ASteering::UpdateRotation()
{
	FVector NewForward = AI->Movement->Velocity;
	NewForward.Normalize();
	FVector NewSide = FVector::CrossProduct(AI->Movement->Velocity, FVector(0.f, 0.f, 0.f));
	FVector NewUp = FVector::CrossProduct(AI->Movement->Velocity, NewSide); 
	AI->SetActorRotation(NewUp.Rotation()); 
}

void ASteering::CallSeek()
{
	FVector DesiredVelocity = Controller->GetActorLocation() - AI->GetActorLocation();
	DesiredVelocity.Normalize();
	DesiredVelocity *= AI->Movement->MaxSpeed;
	AI->Movement->Velocity = DesiredVelocity - AI->Movement->Velocity;
	FVector Acceleration = Truncate(AI->Movement->Velocity, AI->MaxForce) / AI->Mass; 
	FVector VelocityTruncate = Truncate(AI->Movement->Velocity + Acceleration, AI->Movement->MaxSpeed);
	AI->Movement->Velocity = VelocityTruncate;
	AI->SetActorLocation(AI->GetActorLocation() + AI->Movement->Velocity);
}

void ASteering::CallFlee()
{
	//AI->Movement->Velocity = -Seek(); 
}

void ASteering::CallArrival()
{
	float SlowingDistance = 1.f; 
	FVector Offset = Controller->GetActorLocation() - AI->GetActorLocation();
	float Distance = Offset.Size(); 
	float RampedSpeed = AI->Movement->GetMaxSpeed() * (Distance / SlowingDistance);
	float ClippedSpeed = FMath::Min(RampedSpeed, AI->Movement->MaxSpeed); 
	FVector DesiredVelocity = (ClippedSpeed / Distance) * Offset;
    FVector Steering = DesiredVelocity - AI->Movement->Velocity;
	AI->Movement->Velocity = Steering; 
}

// Called when the game starts or when spawned
void ASteering::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASteering::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CallSeek();

}

