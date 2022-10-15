// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/EnemyCharacter.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Engine/EngineTypes.h"
#include "Shared/SurfaceType.h"
#include "Other/ShootingImpactEffect.h"
#include "Enemy/EnemyAIController.h"
#include "Engine/UserDefinedEnum.h"
#include "GameMode/ShootingSystemGameMode.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	//Set Surface Type as flesh for Enemy physical materials to show blood
	SetSurfaceTypeForMaterials(ESurfaceType::ST_FLESH);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemyCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	CurrentHealth = CurrentHealth - Damage;

	KillEnemy();

	return 0.0f;
}

void AEnemyCharacter::KillEnemy()
{
	if (CurrentHealth <= 0)
	{
		CurrentHealth = 0;

		if (!bIsKilled)
		{
			//When killed
			bIsKilled = true;

			//Run ragdoll
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetSimulatePhysics(true);
			GetMesh()->WakeAllRigidBodies();
			GetMesh()->bBlendPhysics = true;
			GetMesh()->SetCollisionResponseToAllChannels(ECR_Block);
			GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
			GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
			GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Ignore);

			//Set Surface Type as empty for Enemy physical materials not to show blood anymore
			SetSurfaceTypeForMaterials(ESurfaceType::ST_EMPTY);

			//Unpossess
			AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(this->GetController());
			if (EnemyAIController)
			{
				EnemyAIController->UnPossess();
			}

		}
	}
	else //When still alive
	{
		//Play stunt animation
	}
}

void AEnemyCharacter::SetSurfaceTypeForMaterials(ESurfaceType SurfaceTypeParam)
{

	const TArray<UMaterialInterface*> Materials = GetMesh()->GetMaterials();

	if (Materials.Num() <= 0)
	{
		return;
	}

	for (int i = 0; i < Materials.Num(); i++)
	{
		UPhysicalMaterial* PhysicalMaterial = nullptr;
		UMaterialInstanceDynamic* MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(Materials[i], this);
		if (MaterialInstanceDynamic)
		{
			PhysicalMaterial = MaterialInstanceDynamic->GetPhysicalMaterial();
			if (PhysicalMaterial)
			{
				AShootingSystemGameMode* ShootingSystemGameMode = Cast<AShootingSystemGameMode>(GetWorld()->GetAuthGameMode());
				if (ShootingSystemGameMode)
				{
					PhysicalMaterial->SurfaceType = ShootingSystemGameMode->GetSurfaceType(SurfaceTypeParam);
				}
			}
		}
	}
}
