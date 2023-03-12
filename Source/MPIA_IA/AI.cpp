// Fill out your copyright notice in the Description page of Project Settings.


#include "AI.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AAI::AAI()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

FVector AAI::Truncate(FVector Vector, float Max)
{
	if (Vector.Length() == 0) return Vector;
	return Vector * Max / Vector.Length();
}

FVector AAI::SeekSteering(FVector Desired, FVector Target, FVector Current)
{
	Desired = (Target - Current);
	Desired.Normalize();
	Desired *= 12.0f;
	return Desired;
}

FVector AAI::ArrivalSteering(FVector Desired, FVector Target, FVector Predicted, FVector Current)
{
	FVector Offset;
	
	Offset = Target - Current;
	
	double Dist = Offset.Length();
	if (Dist <= 50.0f) return FVector(0, 0, 0);

	float RampedSpeed = 12.0f * (Dist / 400.0f);
	float ClippedSpeed = FMath::Min(RampedSpeed, 12.0f);
	Desired = (ClippedSpeed / Dist) * Offset;
	return Desired;
}

FVector AAI::OnePointPathfinding(FVector Desired, FVector Current)
{
	FVector TargetPosition = GetFollowingPath();
	Manager->StartPoint = CurrentTarget; 
	if (bIsFinished)
		return ArrivalSteering(Desired, TargetPosition, TargetPosition, Current);
	else
		return SeekSteering(Desired, TargetPosition, Current);
}

FVector AAI::SeveralPointsPathfinding(FVector Desired, FVector Current)
{
	FVector TargetPosition = GetFollowingPath();
	Manager->StartPoint = CurrentTarget; 
	if (bIsFinished)
		return ArrivalSteering(Desired, TargetPosition, TargetPosition, Current);
	else
		return SeekSteering(Desired, TargetPosition, Current);
}

FVector AAI::CircuitPathfinding(FVector Desired, FVector Current)
{
	FVector TargetPosition = GetFollowingPath();
	Manager->StartPoint = CurrentTarget; 
	if (bIsFinished)
		return ArrivalSteering(Desired, TargetPosition, TargetPosition, Current);
	else
		return SeekSteering(Desired, TargetPosition, Current);
}

FVector AAI::GetFollowingPath()
{
	FVector Current;

	if (!Path.IsEmpty())
	{
		if (!bIsFinished && CurrentNode >= TotalNode - 1) bIsFinished = true;
		
		Current = Path[CurrentNode];
		CurrentTarget = PointPath[CurrentNode];
		
		if (FVector::Dist(Position, Current) <= 100.0f)
		{
			CurrentNode += 1;
			if (CurrentNode >= TotalNode)
				CurrentNode = TotalNode - 1;
		}

		return Current;
	}

	return FVector(0, 0, 0);
}

void AAI::SetupPath(TArray<AGraphPoint*> Actors)
{
	Path.Empty();
	PointPath.Empty();
	TotalNode = 0;
	CurrentNode = 0;

	for (AGraphPoint* Point : Actors)
	{
		Path.Add(Point->GetTransform().GetLocation());
		TotalNode += 1;
		UE_LOG(LogTemp, Warning, TEXT("-> %s"), *Point->GetActorNameOrLabel());
	}
	
	PointPath = Actors;
}

FVector AAI::GetDirection(FVector CurrentPosition, FVector CurrentVelocity, FVector TargetPosition, FVector TargetPredictedPosition)
{
	FVector DesiredVelocity = {0, 0, 0};

	switch(Behaviour)
	{
	case Behaviour::Arrival:
		DesiredVelocity = ArrivalSteering(DesiredVelocity, TargetPosition, TargetPredictedPosition, CurrentPosition);
		break;
		
	case Behaviour::OnlyPoint:
		DesiredVelocity = OnePointPathfinding(DesiredVelocity, CurrentPosition);
		break;

	case Behaviour::SeveralPoints:
		DesiredVelocity = SeveralPointsPathfinding(DesiredVelocity, CurrentPosition);
		break;

	case Behaviour::Circuit:
		DesiredVelocity = CircuitPathfinding(DesiredVelocity, CurrentPosition);
		break;
	
	default:
		break;
	}

	return DesiredVelocity - CurrentVelocity;
}

// Called when the game starts or when spawned
void AAI::BeginPlay()
{
	Super::BeginPlay();

	Position = GetTransform().GetLocation();
	Velocity = GetVelocity();
	
	CurrentTarget = nullptr; 
	Behaviour = Behaviour::Arrival;
	
}

// Called every frame
void AAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bIsArrival = false;

	if (CurrentTarget == nullptr)
	{
		CurrentTarget = Manager->StartPoint;
	}
	
	FVector SteeringDirection(0, 0, 0);

	FVector TargetPosition = CurrentTarget->GetTransform().GetLocation();
	SteeringDirection = GetDirection(Position,Velocity, TargetPosition, TargetPosition + CurrentTarget->GetVelocity() * 0.3f);
	
	Velocity = GetVelocitySteering(SteeringDirection, Velocity, 10.0f);
	if (Velocity.Length() > DBL_EPSILON && !bIsArrival) SetActorRotation(Velocity.Rotation() + FRotator(-90.f, 0.0f, 0.0));
	if(!bIsArrival) Position += Velocity;
	SetActorLocation(Position);
}

FVector AAI::GetVelocitySteering(FVector SteeringDirection, FVector CurrentVelocity, float CurrentMass)
{
	FVector SteeringForce = Truncate(SteeringDirection, 6.0f);
	FVector Acceleration = SteeringForce / CurrentMass;
	FVector Result = CurrentVelocity + Acceleration;
	if (Result.Length() > 12.0f) Result = Truncate(Result, 12.f);
	return Result;
}

// Called to bind functionality to input
void AAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

