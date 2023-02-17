// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node.h"
#include "GameFramework/Actor.h"
#include "Pathfinding.generated.h"

UCLASS()
class MPIA_IA_API APathfinding : public AActor
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ANode*> Circuit;
	
public:	
	// Sets default values for this actor's properties
	APathfinding();

	void FindPath(ANode * Start, ANode * End); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
