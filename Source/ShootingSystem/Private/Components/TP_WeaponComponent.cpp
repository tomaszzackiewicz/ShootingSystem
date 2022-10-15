// Copyright Epic Games, Inc. All Rights Reserved.


#include "Components/TP_WeaponComponent.h"
#include "GameMode/ShootingSystemCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Other/ShootingImpactEffect.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Sound/SoundCue.h"
#include "Enemy/EnemyCharacter.h"
#include "Shared/StaticGlobalProperties.h"
#include "Animation/AnimInstance.h"
#include "Other/ShooterPhysicalMaterial.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector { 100.0f, 0.0f, 10.0f };
}

void UTP_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ImpactTemplate)
	{
		ShootingImpactEffect = GetWorld()->SpawnActor<AShootingImpactEffect>(ImpactTemplate, FVector().ZeroVector, FRotator().ZeroRotator);
	}
	
}

// Called every frame
void UTP_WeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTP_WeaponComponent::Fire()
{
	
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	// Try and play the sound if specified
	PlayShootSound();

	// Try and play a firing animation if specified
	PlayShootAnim();

	//Raycast with each shoot
	ShootRaycast();
}

void UTP_WeaponComponent::PlayShootSound()
{

	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
}

void UTP_WeaponComponent::PlayShootAnim()
{

	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void UTP_WeaponComponent::ShootRaycast()
{

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		//Collect all USkeletalMeshComponents in actor
		const TArray<UActorComponent*> SkeletalMeshComponents = GetOwner()->GetComponentsByClass(USkeletalMeshComponent::StaticClass());

		if (SkeletalMeshComponents.Num() <= 0)
		{
			return;
		}

		USkeletalMeshComponent* SkeletalMeshComponent = nullptr;

		//We asssume there can be many USkeletalMeshComponents in the future, so it is better to find the one we need
		for (auto SkeletalMeshComponentToCheck : SkeletalMeshComponents)
		{
			if (SkeletalMeshComponentToCheck->ComponentHasTag(Gun))
			{
				SkeletalMeshComponent = Cast<USkeletalMeshComponent>(SkeletalMeshComponentToCheck);
				break;
			}
		}

		if (SkeletalMeshComponent)
		{

			const USkeletalMeshSocket* MuzzleSocket = SkeletalMeshComponent->GetSocketByName(Muzzle);

			if (MuzzleSocket)
			{

				const FTransform SocketTransform = MuzzleSocket->GetSocketTransform(SkeletalMeshComponent);

				const FVector Start{ SocketTransform.GetLocation() };
				const FQuat Rotation{ SocketTransform.GetRotation() };
				const FVector RotationAxis{ Rotation.GetAxisX() };
				const FVector End{ Start + RotationAxis * ShootRange };

				FCollisionResponseParams ResponseParams;
				FCollisionQueryParams QueryParams = FCollisionQueryParams::DefaultQueryParam;
				FActorSpawnParameters SpawnParams;
				QueryParams.bReturnPhysicalMaterial = true;
				QueryParams.bTraceComplex = true;
				QueryParams.AddIgnoredActor(GetOwner());
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				TArray<FHitResult> FireHits;
				const bool Hit = World->LineTraceMultiByChannel(FireHits, Start, End, ECollisionChannel::ECC_GameTraceChannel2, QueryParams, ResponseParams);
				FVector BeamEndPoint{ End };

				//DEBUG
				//DrawDebugLine(World, Start, End, FColor::Red, false, 2.0f);
				
				if (!Hit)
				{

					SetTrail(BeamEndPoint, SocketTransform.GetLocation());

					return;
				}

				HandleHitResult(World, FireHits, RotationAxis, SocketTransform.GetLocation());

			}
		}
	}
}

void UTP_WeaponComponent::HandleHitResult(UWorld* WorldParam, TArray<FHitResult> HitResultsParam, const FVector RotationAxisParam, const FVector StartTrailParam)
{

	for (FHitResult& Result : HitResultsParam)
	{
		//Debug
		//DrawDebugPoint(WorldParam, Result.Location, 5.0f, FColor::Red, false, 2.0f);
		
		// Show gun trail (to make the trail work better while we are moving, we need to check the gun's Muzzle socket position every frame in the Tick function)
		//For this task the trail is not needed, but I guess it would be good to show where and how to implement it in the raycasting logic
		SetTrailForGun(Result, StartTrailParam);

		// Deal damage to characters
		DealDamageToCharacter(Result);

		// Deal impulse to actors with physical actors
		bool bIsActorDynamic = AddImpulseToPhysicalActors(Result, RotationAxisParam);

		//Spawn FX stuff for shoot
		SpawnImpactTemplate(WorldParam, Result, bIsActorDynamic);
	}
}

void UTP_WeaponComponent::SetTrailForGun(FHitResult& HitResultParam, const FVector SocketTransformParam)
{

	FVector BeamEndPoint = HitResultParam.Location;

	SetTrail(BeamEndPoint, SocketTransformParam);

}

void UTP_WeaponComponent::SetTrail(FVector BeamEndPointParam, const FVector SocketTransformParam)
{
	if (TrailParticles)
	{
		UParticleSystemComponent* Trail = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TrailParticles, SocketTransformParam);
		if (Trail)
		{
			Trail->SetVectorParameter(ShockBeamEnd, BeamEndPointParam);
		}
	}
}

void UTP_WeaponComponent::SpawnImpactTemplate(UWorld* WorldParam, FHitResult& HitResultParam, bool bIsActorDynamicParam)
{

	if (!ShootingImpactEffect)
	{
		return;
	}

	const EPhysicalSurface PhysicalMaterial = HitResultParam.PhysMaterial->SurfaceType;

	// Get our custom ShooterPhysicalMaterial to check if the hit material is penetrable
	UShooterPhysicalMaterial* ShooterPhysicalMaterial = Cast<UShooterPhysicalMaterial>(HitResultParam.PhysMaterial);

	if (ShooterPhysicalMaterial)
	{
		if (ShooterPhysicalMaterial->GetIsPenetrable())
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Is Penetrable!"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Is NOT Penetrable!"));
		}
	}

	// Show impact particles
	UParticleSystem* ImpactFX = ShootingImpactEffect->GetImpactFX(PhysicalMaterial);
	if (ImpactFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(WorldParam, ImpactFX, HitResultParam.Location);
	}

	if (!bIsActorDynamicParam)
	{ //these decals I have are not good for physical actors, so we skip them if any
	// Place impact decal
		UMaterialInterface* ImpactDecal = ShootingImpactEffect->GetImpactDecal(PhysicalMaterial);
		if (ImpactDecal)
		{
			UGameplayStatics::SpawnDecalAtLocation(WorldParam, ImpactDecal, DecalSize, HitResultParam.Location, HitResultParam.TraceEnd.Rotation());
		}
	}

	// Play impact sound
	USoundCue* ImpactSound = ShootingImpactEffect->GetImpactSound(PhysicalMaterial);
	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(WorldParam, ImpactSound, HitResultParam.Location);
	}
}

void UTP_WeaponComponent::DealDamageToCharacter(FHitResult& HitResultParam)
{

	AActor* Actor = HitResultParam.GetActor();

	if (Actor)
	{
		AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(Actor);

		if (EnemyCharacter)
		{
			UGameplayStatics::ApplyPointDamage(EnemyCharacter, Damage, HitResultParam.ImpactNormal, HitResultParam, nullptr, this->GetOwner(), nullptr);
		}
	}
}

bool UTP_WeaponComponent::AddImpulseToPhysicalActors(FHitResult& HitResultParam, const FVector RotationAxisParam)
{
	bool bIsActorDynamic = false;

	UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(HitResultParam.GetComponent());

	if ((!StaticMeshComponent) || (!HitResultParam.GetActor()->IsRootComponentMovable()))
	{
		return false;
	}

	const FBodyInstance* BodyInstance = StaticMeshComponent->GetBodyInstance();

	if (!BodyInstance)
	{
		return false;
	}

	bIsActorDynamic = BodyInstance->IsDynamic();

	if (bIsActorDynamic)
	{
		StaticMeshComponent->AddImpulse(RotationAxisParam * ImpulseStrength * StaticMeshComponent->GetMass());
	}
	
	return bIsActorDynamic;
}

void UTP_WeaponComponent::AttachWeapon(AShootingSystemCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	if (Character != nullptr)
	{
		// Attach the weapon to the First Person Character
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		GetOwner()->AttachToComponent(Character->GetMesh1P(), AttachmentRules, GripPoint);

		// Register so that Fire is called every time the character tries to use the item being held
		Character->OnUseItem.AddDynamic(this, &UTP_WeaponComponent::Fire);
	}
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (Character != nullptr)
	{
		// Unregister from the OnUseItem Event
		Character->OnUseItem.RemoveDynamic(this, &UTP_WeaponComponent::Fire);
	}
}