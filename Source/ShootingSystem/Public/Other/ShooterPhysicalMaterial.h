// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "ShooterPhysicalMaterial.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGSYSTEM_API UShooterPhysicalMaterial : public UPhysicalMaterial
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicalMaterial", meta = (AllowPrivateAccess = "true"))
	bool bIsPenetrable { false };

public:
	FORCEINLINE bool GetIsPenetrable() const { return bIsPenetrable; }
};
