// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GraphPoint.h"
#include "Node.h"
#include "GameFramework/Actor.h"

class MPIA_IA_API PathfindingAlgo
{

public:

	UPROPERTY(VisibleAnywhere, Category = "Graph")
	TArray<AGraphPoint*> Circuit;
	
public:	
	PathfindingAlgo(); 

	TArray<AGraphPoint*> FindPath(AGraphPoint * Start, AGraphPoint * End);

	void AddPoint(AGraphPoint *Point); 
	
	float CalculateHeuristic(float Cost, AGraphPoint* Start, AGraphPoint* End);

	~PathfindingAlgo();
	
};
