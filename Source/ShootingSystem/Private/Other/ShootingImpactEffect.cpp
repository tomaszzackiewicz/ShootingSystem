// Fill out your copyright notice in the Description page of Project Settings.

#include "Other/ShootingImpactEffect.h"
#include "GameMode/ShootingSystemGameMode.h"

// Sets default values
AShootingImpactEffect::AShootingImpactEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AShootingImpactEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

UParticleSystem* AShootingImpactEffect::GetImpactFX(TEnumAsByte<EPhysicalSurface> SurfaceType) const
{
	UParticleSystem* ImpactFX = NULL;

	switch (SurfaceType)
	{
	case SHOOTER_SURFACE_Concrete:	ImpactFX = ConcreteFX; break;
	case SHOOTER_SURFACE_Dirt:		ImpactFX = DirtFX; break;
	case SHOOTER_SURFACE_Water:		ImpactFX = WaterFX; break;
	case SHOOTER_SURFACE_Metal:		ImpactFX = MetalFX; break;
	case SHOOTER_SURFACE_Wood:		ImpactFX = WoodFX; break;
	case SHOOTER_SURFACE_Grass:		ImpactFX = GrassFX; break;
	case SHOOTER_SURFACE_Glass:		ImpactFX = GlassFX; break;
	case SHOOTER_SURFACE_Flesh:		ImpactFX = FleshFX; break;
	case SHOOTER_SURFACE_Tile:		ImpactFX = TileFX; break;
	case SHOOTER_SURFACE_Empty:		ImpactFX = EmptyFX; break;
	default:						ImpactFX = DefaultFX; break;
	}

	return ImpactFX;
}

UMaterialInterface* AShootingImpactEffect::GetImpactDecal(TEnumAsByte<EPhysicalSurface> SurfaceType) const
{
	UMaterialInterface* ImpactDecal = NULL;

	switch (SurfaceType)
	{
	case SHOOTER_SURFACE_Concrete:	ImpactDecal = ConcreteDecal; break;
	case SHOOTER_SURFACE_Dirt:		ImpactDecal = DirtDecal; break;
	case SHOOTER_SURFACE_Water:		ImpactDecal = WaterDecal; break;
	case SHOOTER_SURFACE_Metal:		ImpactDecal = MetalDecal; break;
	case SHOOTER_SURFACE_Wood:		ImpactDecal = WoodDecal; break;
	case SHOOTER_SURFACE_Grass:		ImpactDecal = GrassDecal; break;
	case SHOOTER_SURFACE_Glass:		ImpactDecal = GlassDecal; break;
	case SHOOTER_SURFACE_Flesh:		ImpactDecal = FleshDecal; break;
	case SHOOTER_SURFACE_Tile:		ImpactDecal = TileDecal; break;
	case SHOOTER_SURFACE_Empty:		ImpactDecal = EmptyDecal; break;
	default:						ImpactDecal = DefaultDecal; break;
	}

	return ImpactDecal;
}

USoundCue* AShootingImpactEffect::GetImpactSound(TEnumAsByte<EPhysicalSurface> SurfaceType) const
{
	USoundCue* ImpactSound = NULL;

	switch (SurfaceType)
	{
	case SHOOTER_SURFACE_Concrete:	ImpactSound = ConcreteSound; break;
	case SHOOTER_SURFACE_Dirt:		ImpactSound = DirtSound; break;
	case SHOOTER_SURFACE_Water:		ImpactSound = WaterSound; break;
	case SHOOTER_SURFACE_Metal:		ImpactSound = MetalSound; break;
	case SHOOTER_SURFACE_Wood:		ImpactSound = WoodSound; break;
	case SHOOTER_SURFACE_Grass:		ImpactSound = GrassSound; break;
	case SHOOTER_SURFACE_Glass:		ImpactSound = GlassSound; break;
	case SHOOTER_SURFACE_Flesh:		ImpactSound = FleshSound; break;
	case SHOOTER_SURFACE_Tile:		ImpactSound = TileSound; break;
	case SHOOTER_SURFACE_Empty:		ImpactSound = EmptySound; break;
	default:						ImpactSound = DefaultSound; break;
	}

	return ImpactSound;
}
