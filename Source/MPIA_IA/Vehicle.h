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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Mass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Velocity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxForce ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxSpeed ;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Point;

public:
	// Sets default values for this pawn's properties
	AVehicle();

	UFUNCTION(BlueprintCallable)
	FVector Seek(); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
