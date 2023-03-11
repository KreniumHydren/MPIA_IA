// Fill out your copyright notice in the Description page of Project Settings.


#include "Node.h"

// Sets default values
NodePoint::NodePoint()
{}

NodePoint::NodePoint(float Cost, float Heuristic, AActor* Point) : COST(Cost), HEURISTIC(Heuristic), POINT(Point) 
{}

bool NodePoint::isFinish(AActor* Point)
{
	return POINT == Point; 
}

bool NodePoint::operator==(const NodePoint& Node) const
{
	return POINT == Node.POINT && COST == Node.COST && HEURISTIC == Node.HEURISTIC && NAME == Node.NAME; 
}
