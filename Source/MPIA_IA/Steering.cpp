// Fill out your copyright notice in the Description page of Project Settings.


#include "Steering.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

FVector Truncate(FVector Vector, float Max) {return (Vector * Max) / Vector.Length();}

// Sets default values
ASteering::ASteering()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void ASteering::CallSeek()
{
	FVector VecDesired = FixedTarget->GetActorLocation() - AI->GetActorLocation();
	if(VecDesired.Length() > 0)
	{
		VecDesired.Normalize();
		VecDesired *= AI->Movement->MaxSpeed;
		FVector VecSteering = VecDesired - AI->Movement->Velocity;
		FVector NewVelocity = AI->Movement->Velocity + VecSteering;
		AI->Movement->Velocity = NewVelocity;
		AI->SetActorLocation(AI->GetActorLocation() + AI->Movement->Velocity);
		AI->SetActorRotation(AI->Movement->Velocity.Rotation());
	}
}

void ASteering::CallFlee()
{
	FVector VecDesired = FixedTarget->GetActorLocation() - AI->GetActorLocation();
	if(VecDesired.Length() > 0)
	{
		VecDesired.Normalize();
		VecDesired *= AI->Movement->MaxSpeed;
		FVector VecSteering = VecDesired - AI->Movement->Velocity;
		FVector NewVelocity = AI->Movement->Velocity + VecSteering;
		AI->Movement->Velocity = -NewVelocity;
		AI->SetActorLocation(AI->GetActorLocation() + AI->Movement->Velocity);
		AI->SetActorRotation(AI->Movement->Velocity.Rotation());
	}
}

void ASteering::CallSeekToController()
{
	FVector VecDesired = Controller->GetActorLocation() - AI->GetActorLocation();
	if(VecDesired.Length() > 0)
	{
		VecDesired.Normalize();
		VecDesired *= AI->Movement->MaxSpeed;
		FVector VecSteering = VecDesired - AI->Movement->Velocity;
		FVector NewVelocity = AI->Movement->Velocity + VecSteering;
		AI->Movement->Velocity = NewVelocity;
		AI->SetActorLocation(AI->GetActorLocation() + AI->Movement->Velocity);
		AI->SetActorRotation(AI->Movement->Velocity.Rotation());
	}
}

void ASteering::CallFleeToController()
{
	FVector VecDesired = Controller->GetActorLocation() - AI->GetActorLocation();
	if(VecDesired.Length() > 0)
	{
		VecDesired.Normalize();
		VecDesired *= AI->Movement->MaxSpeed;
		FVector VecSteering = VecDesired - AI->Movement->Velocity;
		FVector NewVelocity = AI->Movement->Velocity + VecSteering;
		AI->Movement->Velocity = -NewVelocity;
		AI->SetActorLocation(AI->GetActorLocation() + AI->Movement->Velocity);
		AI->SetActorRotation(AI->Movement->Velocity.Rotation());
	}
}

void ASteering::CallArrival()
{
	FVector Offset = Controller->GetActorLocation() - AI->GetActorLocation();
	float Distance = Offset.Size(); 
	float RampedSpeed = AI->Movement->GetMaxSpeed() * (Distance / SlowingDistance);
	float ClippedSpeed = FMath::Min(RampedSpeed, AI->Movement->MaxSpeed);
	AI->Movement->MaxSpeed = ClippedSpeed; 
	FVector DesiredVelocity = (ClippedSpeed / Distance) * Offset;
    FVector Steering = DesiredVelocity - AI->Movement->Velocity;
	AI->Movement->Velocity = Steering;
	AI->SetActorLocation(AI->GetActorLocation() + AI->Movement->Velocity);
	//FMath::RInterpTo(AI->Movement->GetActorTransform().Rotator(), AI->Movement->Velocity.Rotation(), GetWorld()->GetDeltaSeconds(), 5.f);
	AI->SetActorRotation(FMath::RInterpTo(AI->Movement->GetActorTransform().Rotator(), AI->Movement->Velocity.Rotation(), GetWorld()->GetDeltaSeconds(), InterpolationSpeed));
	//AI->SetActorRotation(AI->Movement->Velocity.Rotation());
}

void ASteering::CallCircuit()
{
	ATargetPoint * Target = Circuit[CurrentIndex];
	if(FVector::Dist(AI->GetActorLocation(), Target->GetActorLocation()) <= MarginDistance) {
		CurrentIndex += 1;
		int Length = Circuit.Num();
		if (CurrentIndex >= Length) {
			CurrentIndex = 0;
		}
	}
	FVector Offset = Target->GetActorLocation() - AI->GetActorLocation();
	float Distance = Offset.Size(); 
	float RampedSpeed = AI->Movement->GetMaxSpeed() * (Distance / SlowingDistance);
	float ClippedSpeed = FMath::Min(RampedSpeed, AI->Movement->MaxSpeed); 
	FVector DesiredVelocity = (ClippedSpeed / Distance) * Offset;
	FVector Steering = DesiredVelocity - AI->Movement->Velocity;
	AI->Movement->Velocity = Steering;
	AI->SetActorLocation(AI->GetActorLocation() + AI->Movement->Velocity);
	//FMath::RInterpTo(AI->Movement->GetActorTransform().Rotator(), AI->Movement->Velocity.Rotation(), GetWorld()->GetDeltaSeconds(), 5.f);
	AI->SetActorRotation(FMath::RInterpTo(AI->Movement->GetActorTransform().Rotator(), AI->Movement->Velocity.Rotation(), GetWorld()->GetDeltaSeconds(), InterpolationSpeed));
	//AI->SetActorRotation(AI->Movement->Velocity.Rotation());
}

void ASteering::CallOneWay()
{
	ATargetPoint * Target = Circuit[CurrentIndex];
	if(FVector::Dist(AI->GetActorLocation(), Target->GetActorLocation()) <= MarginDistance) {
		CurrentIndex += 1;
		int Length = Circuit.Num();
		if (CurrentIndex >= Length) {
			CurrentIndex = Length-1;
		}
	}
	FVector Offset = Target->GetActorLocation() - AI->GetActorLocation();
	float Distance = Offset.Size(); 
	float RampedSpeed = AI->Movement->GetMaxSpeed() * (Distance / SlowingDistance);
	float ClippedSpeed = FMath::Min(RampedSpeed, AI->Movement->MaxSpeed); 
	FVector DesiredVelocity = (ClippedSpeed / Distance) * Offset;
	FVector Steering = DesiredVelocity - AI->Movement->Velocity;
	AI->Movement->Velocity = Steering;
	AI->SetActorLocation(AI->GetActorLocation() + AI->Movement->Velocity);
	//FMath::RInterpTo(AI->Movement->GetActorTransform().Rotator(), AI->Movement->Velocity.Rotation(), GetWorld()->GetDeltaSeconds(), 5.f);
	AI->SetActorRotation(FMath::RInterpTo(AI->Movement->GetActorTransform().Rotator(), AI->Movement->Velocity.Rotation(), GetWorld()->GetDeltaSeconds(), InterpolationSpeed));
	//AI->SetActorRotation(AI->Movement->Velocity.Rotation());
}

void ASteering::CallTwoWay()
{
	ATargetPoint * Target = Circuit[CurrentIndex];
	if(FVector::Dist(AI->GetActorLocation(), Target->GetActorLocation()) <= MarginDistance) {
		int Length = Circuit.Num();
		if(StateTwoWay)
		{
			CurrentIndex += 1;
			if (CurrentIndex >= Length) {
				CurrentIndex = Length-1;
				StateTwoWay = false; 
			}
		} else
		{
			CurrentIndex -= 1;
			if(CurrentIndex <= 0)
			{
				CurrentIndex = 0;
				StateTwoWay = true; 
			}
		}
	}
	FVector Offset = Target->GetActorLocation() - AI->GetActorLocation();
	float Distance = Offset.Size(); 
	float RampedSpeed = AI->Movement->GetMaxSpeed() * (Distance / SlowingDistance);
	float ClippedSpeed = FMath::Min(RampedSpeed, AI->Movement->MaxSpeed); 
	FVector DesiredVelocity = (ClippedSpeed / Distance) * Offset;
	FVector Steering = DesiredVelocity - AI->Movement->Velocity;
	AI->Movement->Velocity = Steering;
	AI->SetActorLocation(AI->GetActorLocation() + AI->Movement->Velocity);
	//FMath::RInterpTo(AI->Movement->GetActorTransform().Rotator(), AI->Movement->Velocity.Rotation(), GetWorld()->GetDeltaSeconds(), 5.f);
	AI->SetActorRotation(FMath::RInterpTo(AI->Movement->GetActorTransform().Rotator(), AI->Movement->Velocity.Rotation(), GetWorld()->GetDeltaSeconds(), InterpolationSpeed));
	//AI->SetActorRotation(AI->Movement->Velocity.Rotation());
}

// Called when the game starts or when spawned
void ASteering::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASteering::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if(Mode == "Seek")
	{
		Controller->DisableInput(PlayerController);
		CallSeek();
	} else if(Mode == "Flee") {
		Controller->DisableInput(PlayerController);
		CallFlee();
	} else if(Mode == "Pursuit") {
		Controller->EnableInput(PlayerController);
		CallSeekToController();
	} else if(Mode == "Evade") {
		Controller->EnableInput(PlayerController);
		CallFleeToController(); 
	} else if(Mode == "Arrival") {
		Controller->EnableInput(PlayerController);
		CallArrival(); 
	} else if(Mode == "Circuit") {
		Controller->EnableInput(PlayerController);
		CallCircuit(); 
	} else if(Mode == "OneWay") {
		Controller->EnableInput(PlayerController);
		CallOneWay(); 
	} else if(Mode == "TwoWay")
	{
		Controller->EnableInput(PlayerController);
		CallTwoWay(); 
	}
}