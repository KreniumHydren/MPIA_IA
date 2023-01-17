// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Vehicle.h"
#include "VehicleController.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "Steering.generated.h"

UCLASS()
class MPIA_IA_API ASteering : public AActor
{
	GENERATED_BODY()

	int CurrentIndex = 0;
	bool StateTwoWay = true; 

public:

	UPROPERTY(BlueprintReadWrite) 
	FString Mode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SlowingDistance = 10.f; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AVehicleController *Controller;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AVehicle *AI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ATargetPoint*> Circuit; 

public:	
	// Sets default values for this actor's properties
	ASteering();
	
	UFUNCTION(BlueprintCallable)
	void CallSeek(); 

	UFUNCTION(BlueprintCallable)
	void CallFlee();

	UFUNCTION(BlueprintCallable)
	void CallArrival();

	UFUNCTION(BlueprintCallable)
	void CallCircuit();

	UFUNCTION(BlueprintCallable)
	void CallOneWay();

	UFUNCTION(BlueprintCallable)
	void CallTwoWay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
}; 