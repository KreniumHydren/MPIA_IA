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
		AGraphPoint * Point = Cast<AGraphPoint>(Actor); 
		Pathfinding->AddPoint(Point);
		if (Actor->GetActorNameOrLabel().Equals("BP_GraphPoint_A")) {
			StartPoint = Point;
		}
		if (Actor->GetActorNameOrLabel().Equals("BP_GraphPoint_G")) {
			EndPoint = Point;
		}
	}
}

void AManager::AddPoint(AGraphPoint * Point)
{
	AllPointsSelected.Add(Point);
	UE_LOG(LogTemp, Warning, TEXT("AddPoint"));
}

void AManager::Clear()
{
	AllPointsSelected.Empty(); 
}

TArray<AGraphPoint*> AManager::ShortestPath(AGraphPoint* Start, AGraphPoint* End)
{
	return Pathfinding->FindPath(Start, End); 
}

TArray<AGraphPoint*> AManager::ShortestPathCurrentPoint()
{
	return Pathfinding->FindPath(StartPoint, EndPoint);
}

TArray<AGraphPoint*> AManager::ShortestPathSelectedPoints()
{
	UE_LOG(LogTemp, Warning, TEXT("SelectedPoints"));
	
	TArray<AGraphPoint*> Result;
	TArray<AGraphPoint*> Array;
	AGraphPoint* Last = nullptr;
	bool First = true;

	if (AllPointsSelected.IsEmpty())
	{
		Result.Add(StartPoint);
		return Result;
	}

	UE_LOG(LogTemp, Warning, TEXT("N -> %d"), AllPointsSelected.Num());

	for (AGraphPoint* Point : AllPointsSelected)
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

TArray<AGraphPoint*> AManager::ShortestPathSelectedPointsWithReturn()
{
	TArray<AGraphPoint*> Result;
	TArray<AGraphPoint*> Array;
	AGraphPoint* Last = nullptr;
	bool First = true;

	if (AllPointsSelected.IsEmpty())
	{
		Result.Add(StartPoint);
		return Result;
	}

	for (AGraphPoint* Point : AllPointsSelected)
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
