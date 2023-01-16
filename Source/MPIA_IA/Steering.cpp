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

FVector ASteering::Seek()
{
	FVector DesiredVelocity = UKismetMathLibrary::Subtract_VectorVector(AI->GetActorLocation(), Controller->GetActorLocation()); 
	UKismetMathLibrary::Vector_Normalize(DesiredVelocity, Controller->GetMovementComponent()->GetMaxSpeed()); 
	return UKismetMathLibrary::Subtract_VectorVector(DesiredVelocity, Controller->GetMovementComponent()->Velocity); 
}

void ASteering::CallSeek()
{
	Controller->GetMovementComponent()->Velocity = Seek();
}

void ASteering::Flee()
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

	CallSeek();
	Controller->SetActorLocation(Controller->GetActorLocation() + GetVelocity()); 
}

