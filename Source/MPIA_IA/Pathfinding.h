// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node.h"
#include "GameFramework/Actor.h"

class MPIA_IA_API PathfindingAlgo
{

public:

	UPROPERTY(VisibleAnywhere, Category = "Graph")
	TArray<AActor*> Circuit;
	
public:	
	PathfindingAlgo(); 

	TArray<AActor*> FindPath(AActor * Start, AActor * End);

	void AddPoint(AActor *Point); 
	
	float CalculateHeuristic(float Cost, AActor* Start, AActor* End);

	~PathfindingAlgo();
	
};
