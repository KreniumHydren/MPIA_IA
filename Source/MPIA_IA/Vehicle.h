// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MatrixTypes.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Pawn.h"
#include "Spatial/FastWinding.h"
#include "Vehicle.generated.h"

UCLASS()
class MPIA_IA_API AVehicle : public APawn
{
	GENERATED_BODY()

protected:
	
	FVector Position;
	FVector Velocity;
	FMatrix Orientation; 
	float Mass;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Point;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxSpeed;
	
	FTimerHandle TimerHandle; 

public:
	// Sets default values for this pawn's properties
	AVehicle();

	UFUNCTION(BlueprintCallable)
	void UpdatePosition();

	UFUNCTION(BlueprintCallable)
	void UpdateOrientation();

	UFUNCTION(BlueprintCallable)
	FVector Seek();

	UFUNCTION(BlueprintCallable)
	FVector Flee();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
