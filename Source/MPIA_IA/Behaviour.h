// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class Behaviour : uint8
{
	Arrival,
	OnlyPoint,
	SeveralPoints,
	Circuit
};
