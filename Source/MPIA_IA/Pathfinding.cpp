// Fill out your copyright notice in the Description page of Project Settings.


#include "Pathfinding.h"

// Sets default values
APathfinding::APathfinding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void APathfinding::FindPath(ANode* Start, ANode* End)
{
	TArray<ANode*> Open;
	TArray<ANode*> Closed;
	float h; 

	Open.Add(Start);
	while(!Open.Empty())
	{
		ANode * CurrentNode = Open[0];
		size_t Length = Open.Num();
		if(Length != 1)
		{
			for(size_t index = 0; index < Length; index++)
			{
			
			}
		}

		Open.Remove(CurrentNode);
		Closed.Add(CurrentNode);

		if(CurrentNode == End)
		{
			return;
		}
	}
}

// Called when the game starts or when spawned
void APathfinding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APathfinding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

