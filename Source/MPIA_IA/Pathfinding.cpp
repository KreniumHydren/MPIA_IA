// Fill out your copyright notice in the Description page of Project Settings.


#include "Pathfinding.h"
#include "Node.h"

// Sets default values
PathfindingAlgo::PathfindingAlgo()
{}

TArray<AActor*> PathfindingAlgo::FindPath(AActor* Start, AActor* End)
{
	if(!Start || !End) return TArray<AActor*>();
	
	TArray<NodePoint*> File;
	TArray<AActor*> FileVisited;

	float C = 0.0f;
	float H = 0.0f;
	
	File.Add(new NodePoint(C, H, Start));

	TArray<AActor*> Path;
	
	NodePoint* Visited; 
	
	while (!File.IsEmpty())
	{
		NodePoint* Node = File[0];

		C = C + 1;

		if (Node->isFinish(End))
		{
			Path.Add(Node->POINT);
			File.Empty();
			FileVisited.Empty();
			return Path;
		}
		
		TArray<AActor*> Neighbors = Node->Neighbors;
		for (AActor* N : Neighbors)
		{
			C = CalculateHeuristic(C, N, End);
			Visited = new NodePoint(C,H,N); 

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

void PathfindingAlgo::AddPoint(AActor* Point)
{
	Circuit.Add(Point); 
}

float PathfindingAlgo::CalculateHeuristic(float Cost, AActor* Start, AActor* End)
{
	return (Cost + Start->GetDistanceTo(End));
}

PathfindingAlgo::~PathfindingAlgo()
{}

