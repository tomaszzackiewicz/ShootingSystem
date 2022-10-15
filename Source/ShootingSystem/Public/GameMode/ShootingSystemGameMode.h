// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Shared/SurfaceType.h"
#include "ShootingSystemGameMode.generated.h"

#define SHOOTER_SURFACE_Default		SurfaceType_Default
#define SHOOTER_SURFACE_Concrete	SurfaceType1
#define SHOOTER_SURFACE_Dirt		SurfaceType2
#define SHOOTER_SURFACE_Water		SurfaceType3
#define SHOOTER_SURFACE_Metal		SurfaceType4
#define SHOOTER_SURFACE_Wood		SurfaceType5
#define SHOOTER_SURFACE_Grass		SurfaceType6
#define SHOOTER_SURFACE_Glass		SurfaceType7
#define SHOOTER_SURFACE_Flesh		SurfaceType8
#define SHOOTER_SURFACE_Tile		SurfaceType9
#define SHOOTER_SURFACE_Empty		SurfaceType10

UCLASS(minimalapi)
class AShootingSystemGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShootingSystemGameMode();

	EPhysicalSurface GetSurfaceType(ESurfaceType SurfaceTypeParam) const;
};



