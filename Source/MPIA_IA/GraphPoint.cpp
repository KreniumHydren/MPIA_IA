// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphPoint.h"

// Sets default values
AGraphPoint::AGraphPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGraphPoint::BeginPlay()
{
	Super::BeginPlay();

	NeighborsNum = Neighbors.Max();

	//UE_LOG(LogTemp, Warning, TEXT("Actors position : [%d,%d]."), parent->GetActorLocation().X, parent->GetActorLocation().Y);

	for (size_t count = 0; count < NeighborsNum - 1; count++)
	{
		NeighborsDist.Add(Parent->GetDistanceTo(Neighbors[count]));
	}
	
}

// Called every frame
void AGraphPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

