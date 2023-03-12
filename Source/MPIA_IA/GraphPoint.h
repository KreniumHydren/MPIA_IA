// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GraphPoint.generated.h"

UCLASS()
class MPIA_IA_API AGraphPoint : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere)
	int NeighborsNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
	TArray<AGraphPoint*> Neighbors;
	
	UPROPERTY(VisibleAnywhere)
	TArray<float> NeighborsDist;

	UPROPERTY(EditAnywhere, Category = "Point")
	AGraphPoint* Parent;
	
public:	
	// Sets default values for this actor's properties
	AGraphPoint();

	UFUNCTION(BlueprintGetter)
	TArray<AGraphPoint*> GetNeighbors()
	{
		return Neighbors; 
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
