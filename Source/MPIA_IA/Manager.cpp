// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager.h"

#include "GraphPoint.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AManager::AManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AManager::Initialize()
{
	TArray<AActor*> AllActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGraphPoint::StaticClass(), AllActors);

	for (AActor* Actor : AllActors)
	{
		Pathfinding->AddPoint(Actor);
		if (Actor->GetActorNameOrLabel().Equals("BP_GraphPoint_A")) StartPoint =Actor;
		if (Actor->GetActorNameOrLabel().Equals("BP_GraphPoint_G")) EndPoint = Actor;
	}
}

void AManager::AddPoint(AActor * Point)
{
	AllPointsSelected.Add(Point); 
}

void AManager::Clear()
{
	AllPointsSelected.Empty(); 
}

TArray<AActor*> AManager::ShortestPath(AActor* Start, AActor* End)
{
	return Pathfinding->FindPath(Start, End); 
}

TArray<AActor*> AManager::ShortestPathCurrentPoint(AActor* Start, AActor* End)
{
	return Pathfinding->FindPath(StartPoint, EndPoint);
}

TArray<AActor*> AManager::ShortestPathSelectedPoints()
{
	TArray<AActor*> Result;
	TArray<AActor*> Array;
	AActor* Last = nullptr;
	bool First = true;

	if (AllPointsSelected.IsEmpty())
	{
		Result.Add(StartPoint);
		return Result;
	}

	for (AActor* Point : AllPointsSelected)
	{
		if (First)
		{
			Result = Pathfinding->FindPath(StartPoint, Point);
			Last = Point;
			First = false;
		}
		else {
			Array = Pathfinding->FindPath(Last, Point);
			Result.Append(Array);
			Array.Empty();
			Last = Point;
		}
	}

	return Result; 
}

TArray<AActor*> AManager::ShortestPathSelectedPointsWithReturn()
{
	TArray<AActor*> Result;
	TArray<AActor*> Array;
	AActor* Last = nullptr;
	bool First = true;

	if (AllPointsSelected.IsEmpty())
	{
		Result.Add(StartPoint);
		return Result;
	}

	for (AActor* Point : AllPointsSelected)
	{
		if (First)
		{
			Result = Pathfinding->FindPath(StartPoint, Point);
			Last = Point;
			First = false;
		}
		else {
			Array = Pathfinding->FindPath(Last, Point);
			Result.Append(Array);
			Array.Empty();
			Last = Point;
		}
	}

	Array = Pathfinding->FindPath(Last, StartPoint);
	Result.Append(Array);
	Array.Empty();
	Last = StartPoint;

	return Result; 
}

// Called when the game starts or when spawned
void AManager::BeginPlay()
{
	Super::BeginPlay();

	Initialize(); 
	
}

// Called every frame
void AManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

