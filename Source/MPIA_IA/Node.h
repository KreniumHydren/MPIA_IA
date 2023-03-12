// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GraphPoint.h"
#include "GameFramework/Actor.h"

class MPIA_IA_API NodePoint
{

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float COST = 1.0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bVisited = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NAME; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HEURISTIC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGraphPoint* POINT;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AGraphPoint*> Neighbors; 
	
public:	
	// Sets default values for this actor's properties
	NodePoint();

	NodePoint(float Cost, float Heuristic, AGraphPoint* Point);
	
	NodePoint(float Cost, float Heuristic, FName Name, AGraphPoint* Point);

	NodePoint(float Cost, float Heuristic, AGraphPoint* Point, TArray<AGraphPoint*> Neighbors);
	
	bool isFinish(AGraphPoint* Point);
    
    inline bool operator==(const NodePoint& Node) const;

	~NodePoint(); 

};
