// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "SurfaceType.generated.h"

/** keep in sync with ShooterImpactEffect */
UENUM()
enum class ESurfaceType : uint8
{
	ST_UKNOWN = 0,
	ST_CONCRETE = 1,
	ST_DIRT = 2,
	ST_WATER = 3,
	ST_METAL = 4,
	ST_WOOD = 5,
	ST_GRASS = 6,
	ST_GLASS = 7,
	ST_FLESH = 8,
	ST_TILE = 9,
	ST_EMPTY = 10
};