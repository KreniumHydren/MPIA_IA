// Fill out your copyright notice in the Description page of Project Settings.


#include "Pathfinding.h"
#include "Node.h"

// Sets default values
PathfindingAlgo::PathfindingAlgo()
{}

TArray<AGraphPoint*> PathfindingAlgo::FindPath(AGraphPoint* Start, AGraphPoint* End)
{
	if(Start == nullptr || End == nullptr) return TArray<AGraphPoint*>();
	
	TArray<NodePoint*> File;
	TArray<AGraphPoint*> FileVisited;

	float C = 0.0f;
	float H = 0.0f;
	
	File.Add(new NodePoint(C, H, Start, Start->Neighbors));
	
	TArray<AGraphPoint*> Path;
	
	while (!File.IsEmpty())
	{
		NodePoint* Node = File[0];
		
		C = C + 1;

		if (Node->isFinish(End))
		{
			UE_LOG(LogTemp, Warning, TEXT("Path found !"));
			
			Path.Add(Node->POINT);
			File.Empty();
			FileVisited.Empty();
			return Path;
		}
		
		TArray<AGraphPoint*> Neighbors = Node->Neighbors;
		for (AGraphPoint* N : Neighbors)
		{
			UE_LOG(LogTemp, Warning, TEXT("N -> %s"), *N->GetActorNameOrLabel());
			H = CalculateHeuristic(C, N, End);
			NodePoint* Visited = new NodePoint(C,H,N, N->Neighbors); 

			if (!FileVisited.Contains(N) || (File.Contains(Visited) && File[File.Find(Visited)]->COST < C))
			{
				File.Add(Visited);
			}
		}

		File.Remove(Node);
		File.Sort([](const NodePoint& Node1, const NodePoint& Node2) {
			return Node1.HEURISTIC < Node2.HEURISTIC;
		});
		FileVisited.Add(Node->POINT);
		Path.Add(Node->POINT);
	}
	
	File.Empty();
	FileVisited.Empty();
	return Path;
}

void PathfindingAlgo::AddPoint(AGraphPoint* Point)
{
	Circuit.Add(Point); 
}

float PathfindingAlgo::CalculateHeuristic(float Cost, AGraphPoint* Start, AGraphPoint* End)
{
	return (Cost + Start->GetDistanceTo(End));
}

PathfindingAlgo::~PathfindingAlgo()
{}

