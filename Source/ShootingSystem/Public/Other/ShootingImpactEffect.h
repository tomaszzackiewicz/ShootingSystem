// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Pool/PooledObject.h"
#include "ShootingImpactEffect.generated.h"

class UMaterialInterface;
class UParticleSystem;
class USoundCue;

UCLASS()
class AShootingImpactEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShootingImpactEffect();

	/** get FX for material type */
	UParticleSystem* GetImpactFX(TEnumAsByte<EPhysicalSurface> SurfaceType) const;

	/** get FX for material type */
	UMaterialInterface* GetImpactDecal(TEnumAsByte<EPhysicalSurface> SurfaceType) const;

	/** get sound for material type */
	USoundCue* GetImpactSound(TEnumAsByte<EPhysicalSurface> SurfaceType) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** default impact FX used when material specific override doesn't exist */
	UPROPERTY(EditDefaultsOnly, Category = Defaults)
	UParticleSystem* DefaultFX;

	/** impact FX on concrete */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* ConcreteFX;

	/** impact FX on dirt */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* DirtFX;

	/** impact FX on water */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* WaterFX;

	/** impact FX on metal */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* MetalFX;

	/** impact FX on wood */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* WoodFX;

	/** impact FX on glass */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* GlassFX;

	/** impact FX on grass */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* GrassFX;

	/** impact FX on flesh */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* FleshFX;

	/** impact FX on tile */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* TileFX;

	/** impact FX on empty */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* EmptyFX;


	/** default impact decal used when material specific override doesn't exist */
	UPROPERTY(EditDefaultsOnly, Category = Defaults)
	UMaterialInterface* DefaultDecal;

	/** impact decal on concrete */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UMaterialInterface* ConcreteDecal;

	/** impact decal on dirt */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UMaterialInterface* DirtDecal;

	/** impact decal on water */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UMaterialInterface* WaterDecal;

	/** impact FX on metal */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UMaterialInterface* MetalDecal;

	/** impact decal on wood */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UMaterialInterface* WoodDecal;

	/** impact decal on glass */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UMaterialInterface* GlassDecal;

	/** impact decal on grass */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UMaterialInterface* GrassDecal;

	/** impact decal on flesh */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UMaterialInterface* FleshDecal;

	/** impact decal on tile */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UMaterialInterface* TileDecal;

	/** impact decal on empty */
	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UMaterialInterface* EmptyDecal;


	/** default impact sound used when material specific override doesn't exist */
	UPROPERTY(EditDefaultsOnly, Category = Defaults)
	class USoundCue* DefaultSound;

	/** impact FX on concrete */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* ConcreteSound;

	/** impact FX on dirt */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* DirtSound;

	/** impact FX on water */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* WaterSound;

	/** impact FX on metal */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* MetalSound;

	/** impact FX on wood */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* WoodSound;

	/** impact FX on glass */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* GlassSound;

	/** impact FX on grass */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* GrassSound;

	/** impact FX on flesh */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* FleshSound;

	/** impact FX on tile */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* TileSound;

	/** impact FX on empty */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* EmptySound;

	/** surface data for spawning */
	UPROPERTY(BlueprintReadOnly, Category = Surface)
	FHitResult SurfaceHit;

};
