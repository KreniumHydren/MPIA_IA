// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Behaviour.h"
#include "Manager.h"
#include "GameFramework/Pawn.h"
#include "AI.generated.h"

UCLASS()
class MPIA_IA_API AAI : public APawn
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget), Category = "Steering")
	FVector Position;

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget), Category = "Steering")
	FVector Velocity;

	UPROPERTY(BlueprintReadOnly, Category = "Node")
	AGraphPoint* CurrentTarget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget), Category = "Pathfinding")
	TArray<FVector> Path;

	UPROPERTY(VisibleAnywhere, Category = "Pathfinding")
	TArray<AGraphPoint*> PointPath;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Manager")
	AManager * Manager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Node")
	bool bIsFinished = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Node")
	bool bIsArrival = false; 

	UPROPERTY(VisibleAnywhere, Category = "Node")
	int CurrentNode = 0;

	UPROPERTY(VisibleAnywhere, Category = "Node")
	int TotalNode = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget), Category = "Widget")
	Behaviour Behaviour;

public:
	// Sets default values for this pawn's properties
	AAI();
	
	FVector Truncate(FVector Vector, float Max);

	UFUNCTION(BlueprintCallable, Category = "Steering")
	FVector SeekSteering(FVector Desired, FVector Target, FVector Current);

	UFUNCTION(BlueprintCallable, Category = "Steering")
	FVector ArrivalSteering(FVector Desired, FVector Target, FVector Predicted, FVector Current);

	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	FVector OnePointPathfinding(FVector Desired, FVector Current);

	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	FVector SeveralPointsPathfinding(FVector Desired, FVector Current);

	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	FVector CircuitPathfinding(FVector Desired, FVector Current);

	UFUNCTION(BlueprintCallable, Category = "Steering")
	FVector GetDirection(FVector CurrentPosition, FVector CurrentVelocity, FVector TargetPosition, FVector TargetPredictedPosition); 
	
	UFUNCTION(BlueprintCallable, Category = "Steering")
	FVector GetVelocitySteering(FVector SteeringDirection, FVector CurrentVelocity, float CurrentMass); 

	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	FVector GetFollowingPath();
	
	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	void SetupPath(TArray<AGraphPoint*> Actors); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
