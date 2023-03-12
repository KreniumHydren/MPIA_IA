// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GraphPoint.h"
#include "Pathfinding.h"
#include "GameFramework/Actor.h"
#include "Manager.generated.h"

UCLASS()
class MPIA_IA_API AManager : public AActor
{
	GENERATED_BODY()

public:
	
	PathfindingAlgo * Pathfinding = new PathfindingAlgo(); 

	UPROPERTY(VisibleAnywhere, Category = "Pathfinding")
	TArray<AGraphPoint*> AllPointsSelected;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pathfinding")
	AGraphPoint* StartPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pathfinding")
	AGraphPoint* EndPoint;
	
public:	
	// Sets default values for this actor's properties
	AManager();

	void Initialize(); 

	UFUNCTION(BlueprintCallable)
	void AddPoint(AGraphPoint * Point);

	UFUNCTION(BlueprintCallable)
	void Clear(); 

	UFUNCTION(BlueprintCallable)
	TArray<AGraphPoint*> ShortestPath(AGraphPoint* Start, AGraphPoint* End);

	UFUNCTION(BlueprintCallable)
	TArray<AGraphPoint*> ShortestPathCurrentPoint();
	
	UFUNCTION(BlueprintCallable)
	TArray<AGraphPoint*> ShortestPathSelectedPoints();

	UFUNCTION(BlueprintCallable)
	TArray<AGraphPoint*> ShortestPathSelectedPointsWithReturn();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
