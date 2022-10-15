// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameMode/ShootingSystemGameMode.h"
#include "GameMode/ShootingSystemCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Shared/SurfaceType.h"

AShootingSystemGameMode::AShootingSystemGameMode(){
	
}

EPhysicalSurface AShootingSystemGameMode::GetSurfaceType(ESurfaceType SurfaceTypeParam) const
{
	EPhysicalSurface SurfaceType = EPhysicalSurface::SurfaceType_Default;

	switch (SurfaceTypeParam)
	{
	case ESurfaceType::ST_CONCRETE:		SurfaceType = EPhysicalSurface::SurfaceType1; break;
	case ESurfaceType::ST_DIRT:			SurfaceType = EPhysicalSurface::SurfaceType2; break;
	case ESurfaceType::ST_WATER:		SurfaceType = EPhysicalSurface::SurfaceType3; break;
	case ESurfaceType::ST_METAL:		SurfaceType = EPhysicalSurface::SurfaceType4; break;
	case ESurfaceType::ST_WOOD:			SurfaceType = EPhysicalSurface::SurfaceType5; break;
	case ESurfaceType::ST_GRASS:		SurfaceType = EPhysicalSurface::SurfaceType6; break;
	case ESurfaceType::ST_GLASS:		SurfaceType = EPhysicalSurface::SurfaceType7; break;
	case ESurfaceType::ST_FLESH:		SurfaceType = EPhysicalSurface::SurfaceType8; break;
	case ESurfaceType::ST_TILE:			SurfaceType = EPhysicalSurface::SurfaceType9; break;
	case ESurfaceType::ST_EMPTY:		SurfaceType = EPhysicalSurface::SurfaceType10; break;
	default:							SurfaceType = EPhysicalSurface::SurfaceType_Default; break;
	}

	return SurfaceType;
}