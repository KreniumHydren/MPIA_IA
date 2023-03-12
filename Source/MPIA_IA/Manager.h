// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	TArray<AActor*> AllPointsSelected;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pathfinding")
	AActor* StartPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pathfinding")
	AActor* EndPoint;
	
public:	
	// Sets default values for this actor's properties
	AManager();

	void Initialize(); 

	UFUNCTION(BlueprintCallable)
	void AddPoint(AActor * Point);

	UFUNCTION(BlueprintCallable)
	void Clear(); 

	UFUNCTION(BlueprintCallable)
	TArray<AActor*> ShortestPath(AActor* Start, AActor* End);

	UFUNCTION(BlueprintCallable)
	TArray<AActor*> ShortestPathCurrentPoint(AActor* Start, AActor* End);
	
	UFUNCTION(BlueprintCallable)
	TArray<AActor*> ShortestPathSelectedPoints();

	UFUNCTION(BlueprintCallable)
	TArray<AActor*> ShortestPathSelectedPointsWithReturn();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
