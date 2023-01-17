// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Vehicle.h"
#include "VehicleController.h"
#include "GameFramework/Actor.h"
#include "Steering.generated.h"

UCLASS()
class MPIA_IA_API ASteering : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AVehicleController *Controller;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AVehicle *AI;

public:	
	// Sets default values for this actor's properties
	ASteering();

	UFUNCTION(BlueprintCallable)
	void UpdatePosition();
	
	UFUNCTION(BlueprintCallable)
	void UpdateRotation(); 

	UFUNCTION(BlueprintCallable)
	FVector Seek();
	
	UFUNCTION(BlueprintCallable)
	void CallSeek(); 

	UFUNCTION(BlueprintCallable)
	void CallFlee();

	UFUNCTION(BlueprintCallable)
	void CallArrival(); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
}; 