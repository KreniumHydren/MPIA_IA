// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Vehicle.h"
#include "GameFramework/Actor.h"
#include "Steering.generated.h"

UCLASS()
class MPIA_IA_API ASteering : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AVehicle *Controller;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh *ControllerMesh; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AVehicle *AI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh *AIMesh; 
	
public:	
	// Sets default values for this actor's properties
	ASteering();

	UFUNCTION(BlueprintCallable)
	FVector Seek();
	
	UFUNCTION(BlueprintCallable)
	void CallSeek(); 

	UFUNCTION(BlueprintCallable)
	void Flee();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
