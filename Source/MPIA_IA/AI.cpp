// Fill out your copyright notice in the Description page of Project Settings.


#include "AI.h"

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
	
	double distance = Offset.Length();
	if (distance <= 50.0f) return FVector(0, 0, 0);

	float ramped_speed = 12.0f * (distance / 400.0f);
	float clipped_speed = FMath::Min(ramped_speed, 12.0f);
	Desired = (clipped_speed / distance) * Offset;
	return Desired;
}

FVector AAI::OnePointPathfinding(FVector Desired, FVector Current)
{
	FVector TargetPosition = GetFollowingPath();
	Manager->StartPoint = TargetNode; 
	if (bIsFinished)
		return ArrivalSteering(Desired, TargetPosition, TargetPosition, Current);
	else
		return SeekSteering(Desired, TargetPosition, Current);
}

FVector AAI::SeveralPointsPathfinding(FVector Desired, FVector Current)
{
	FVector TargetPosition = GetFollowingPath();
	Manager->StartPoint = TargetNode; 
	if (bIsFinished)
		return ArrivalSteering(Desired, TargetPosition, TargetPosition, Current);
	else
		return SeekSteering(Desired, TargetPosition, Current);
}

FVector AAI::CircuitPathfinding(FVector Desired, FVector Current)
{
	FVector TargetPosition = GetFollowingPath();
    	Manager->StartPoint = TargetNode; 
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
		
		Current = PositionPath[CurrentNode];
		TargetNode = Path[CurrentNode];

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

void AAI::SetupPath(TArray<AActor*> Actors)
{
	PositionPath.Empty();
	Path.Empty();
	TotalNode = 0;
	CurrentNode = 0;

	for (AActor* Actor : Actors)
	{
		PositionPath.Add(Actor->GetTransform().GetLocation());
		TotalNode += 1;
	}
	
	Path = Actors;
}

FVector AAI::GetDirection(FVector CurrentPostion, FVector CurrentVelocity, FVector TargetPosition, FVector TargetPredictedPosition)
{
	FVector DesiredVelocity = {0, 0, 0};

	switch(Behaviour)
	{
	case Behaviour::OnlyPoint:
		DesiredVelocity = OnePointPathfinding(DesiredVelocity, CurrentPostion);
		break;

	case Behaviour::SeveralPoints:
		DesiredVelocity = SeveralPointsPathfinding(DesiredVelocity, CurrentPostion);
		break;

	case Behaviour::Circuit:
		DesiredVelocity = CircuitPathfinding(DesiredVelocity, CurrentPostion);
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
	Velocity = this->GetVelocity();
	
}

// Called every frame
void AAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	arrival = false;

	if (target == nullptr)
		target = manager_component->GetStartPointSelect();

	FVector steering_direction(0, 0, 0);

	FVector target_position = target->GetTransform().GetLocation();
	steering_direction = Get_Steering_Direction(position,velocity, target_position, target_position + target->GetVelocity() * prediction_factor);
	
	velocity = Calculate_Velocity(steering_direction, velocity, mass);
	if (velocity.Length() > DBL_EPSILON && !arrival)
		SetActorRotation(velocity.Rotation() + FRotator(-90.f, 0.0f, 0.0));
	
	// position = position + velocity;
	if(!arrival)
		position = position + velocity;

	SetActorLocation(position);

}

FVector AVehicle::Calculate_Velocity(FVector steering_direction, FVector current_velocity, float current_mass)
{
	// steering_force = truncate(steering_direction, max_force);
	FVector steering_force = truncate(steering_direction, max_force);
	// acceleration = steering_force / mass;
	FVector acceleration = steering_force / current_mass;
	// velocity = truncate(velocity + acceleration, max_speed);
	FVector result = current_velocity + acceleration;
	if (result.Length() > max_speed)
		result = truncate(result, max_speed);
	return result;
}

// Called to bind functionality to input
void AAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

