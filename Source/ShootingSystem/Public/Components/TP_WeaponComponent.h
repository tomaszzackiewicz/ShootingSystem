// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TP_WeaponComponent.generated.h"

class AShootingSystemCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTINGSYSTEM_API UTP_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	/** Sets default values for this component's properties */
	UTP_WeaponComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AttachWeapon(AShootingSystemCharacter* TargetCharacter);

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	FVector MuzzleOffset {100.0f, 0.0f, 0.0f };

	/** Size of impact decal on material */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	FVector DecalSize { 10.0f, 10.0f, 10.0f };

	/** Range of shoot raycast */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	float ShootRange { 50000.0f };

	/** Amount of shoot damage */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	int32 Damage { 10} ;

	/** Strength of impulse for physics actors */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	float ImpulseStrength { 1000.0f };

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	USoundBase* FireSound = nullptr;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* FireAnimation = nullptr;

	/** Smoke trail for bullets */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* TrailParticles = nullptr;

	/** Impact effects, sounds, and decals */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AShootingImpactEffect> ImpactTemplate = NULL;

	/** The Character holding this weapon*/
	AShootingSystemCharacter* Character = nullptr;

	int32 SkeletalMeshComponentsIndex{ 0 };

	AShootingImpactEffect* ShootingImpactEffect = nullptr;

	void PlayShootSound();
	void PlayShootAnim();
	void ShootRaycast();
	void HandleHitResult(UWorld* WorldParam, TArray<FHitResult> HitResultsParam, const FVector RotationAxisParam, const FVector StartTrailParam);
	void SetTrailForGun(FHitResult& HitResultParam, const FVector SocketTransformParam);
	void SetTrail(FVector BeamEndPointParam, FVector SocketTransformParam);
	void SpawnImpactTemplate(UWorld* WorldParam, FHitResult& HitResultParam, bool bIsActorDynamicParam);
	void DealDamageToCharacter(FHitResult& HitResultParam);
	bool AddImpulseToPhysicalActors(FHitResult& HitResultParam, const FVector RotationAxisParam);
};
