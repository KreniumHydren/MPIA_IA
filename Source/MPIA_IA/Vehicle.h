// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "Vehicle.generated.h"

UCLASS()
class MPIA_IA_API AVehicle : public APawn
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxSpeedEffective = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxForce = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Mass = 20.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovement *Movement; 

public:
	// Sets default values for this pawn's properties
	AVehicle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
