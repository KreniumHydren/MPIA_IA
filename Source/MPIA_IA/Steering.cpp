// Fill out your copyright notice in the Description page of Project Settings.


#include "Steering.h"

#include <UIAutomationCore.h>

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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

void ASteering::UpdatePosition()
{
	//FVector VelocityTruncate = Truncate(Controller->Movement->Velocity + Controller->Movement->Acceleration, Controller->Movement->MaxSpeed);
	//Controller->Movement->Velocity = VelocityTruncate;
	AI->SetActorLocation(AI->GetActorLocation() + AI->Movement->Velocity);
}

void ASteering::UpdateRotation()
{
	FVector NewForward = AI->GetVelocity(); 
	UKismetMathLibrary::Vector_Normalize(NewForward);
	FVector NewSide = FVector::CrossProduct(AI->GetVelocity(), FVector(0.f, 0.f, 0.f));
	FVector NewUp = FVector::CrossProduct(AI->GetVelocity(), NewSide); 
	AI->SetActorRotation(NewUp.Rotation()); 
}

FVector ASteering::Seek()
{
	FVector DesiredVelocity = UKismetMathLibrary::Subtract_VectorVector(Controller->GetActorLocation(), AI->GetActorLocation()); 
	UKismetMathLibrary::Vector_Normalize(DesiredVelocity, AI->Movement->MaxSpeed); 
	return UKismetMathLibrary::Subtract_VectorVector(DesiredVelocity, AI->GetMovementComponent()->Velocity); 
}

void ASteering::CallSeek()
{
	AI->GetMovementComponent()->Velocity = Seek();
}

void ASteering::CallFlee()
{
	AI->GetMovementComponent()->Velocity = -Seek(); 
}

void ASteering::CallArrival()
{
	float SlowingDistance = 0.f; 
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
	UpdatePosition();
	//UpdateRotation();
}

