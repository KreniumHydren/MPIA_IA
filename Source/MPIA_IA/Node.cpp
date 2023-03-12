// Fill out your copyright notice in the Description page of Project Settings.


#include "Node.h"

// Sets default values
NodePoint::NodePoint()
{}

NodePoint::NodePoint(float Cost, float Heuristic, AGraphPoint* Point) : COST(Cost), HEURISTIC(Heuristic), POINT(Point) 
{}

NodePoint::NodePoint(float Cost, float Heuristic, AGraphPoint* Point, TArray<AGraphPoint*> Neighbors) : COST(Cost), HEURISTIC(Heuristic), POINT(Point), Neighbors(Neighbors)
{}

bool NodePoint::isFinish(AGraphPoint* Point)
{
	return POINT == Point; 
}

bool NodePoint::operator==(const NodePoint& Node) const
{
	return POINT == Node.POINT && COST == Node.COST && HEURISTIC == Node.HEURISTIC && NAME == Node.NAME; 
}
