// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VehicleController.generated.h"

UCLASS()
class MPIA_IA_API AVehicleController : public APawn
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float MaxSpeedEffective;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float LengthInput = 25.0;

    FVector MovementDirection;

	UFUNCTION()
    void MoveForward(float Value); 

	UFUNCTION()
	void MoveRight(float Value);

public:
	// Sets default values for this pawn's properties
	AVehicleController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
