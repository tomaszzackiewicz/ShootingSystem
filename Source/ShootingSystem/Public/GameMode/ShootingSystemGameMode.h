// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Shared/SurfaceType.h"
#include "ShootingSystemGameMode.generated.h"

UCLASS(minimalapi)
class AShootingSystemGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShootingSystemGameMode();

	EPhysicalSurface GetSurfaceType(ESurfaceType SurfaceTypeParam) const;
};



