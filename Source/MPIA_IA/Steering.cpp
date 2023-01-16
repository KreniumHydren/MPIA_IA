// Fill out your copyright notice in the Description page of Project Settings.


#include "Steering.h"

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
	//UE_LOG(LogTemp, Warning, TEXT("PositionVelocity : %s"), *VelocityTruncate.ToString());
	Controller->SetActorLocation(Controller->GetActorLocation() + Controller->Movement->Velocity);
}

void ASteering::UpdateRotation()
{
	FVector NewForward = Controller->GetVelocity(); 
	UKismetMathLibrary::Vector_Normalize(NewForward);
	FVector NewSide = FVector::CrossProduct(Controller->GetVelocity(), FVector(0.f, 0.f, 0.f));
	FVector NewUp = FVector::CrossProduct(Controller->GetVelocity(), NewSide); 
	Controller->SetActorRotation(NewUp.Rotation()); 
}

FVector ASteering::Seek()
{
	FVector DesiredVelocity = UKismetMathLibrary::Subtract_VectorVector(AI->GetActorLocation(), Controller->GetActorLocation()); 
	UKismetMathLibrary::Vector_Normalize(DesiredVelocity, Controller->Movement->MaxSpeed); 
	return UKismetMathLibrary::Subtract_VectorVector(DesiredVelocity, Controller->GetMovementComponent()->Velocity); 
}

void ASteering::CallSeek()
{
	Controller->GetMovementComponent()->Velocity = Seek();
}

void ASteering::CallFlee()
{
	Controller->GetMovementComponent()->Velocity = -Seek(); 
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
	CallFlee();
	UpdatePosition();
	UpdateRotation();
}

