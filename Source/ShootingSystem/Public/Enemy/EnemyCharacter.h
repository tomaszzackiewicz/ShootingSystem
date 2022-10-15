// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Shared/SurfaceType.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class SHOOTINGSYSTEM_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void KillEnemy();

	void SetSurfaceTypeForMaterials(ESurfaceType SurfaceTypeParam);

	/** Max health of enemy */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	int MaxHealth { 100 };

	/** Current health of enemy */
	int CurrentHealth { 0 };

	bool bIsKilled { false };

};
