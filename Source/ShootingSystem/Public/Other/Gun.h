// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class AShootingSystemCharacter;
class UTP_WeaponComponent;
class UTP_PickUpComponent;
class USkeletalMeshComponent;

UCLASS()
class SHOOTINGSYSTEM_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UTP_PickUpComponent* GetTP_PickUpComponent() const { return TP_PickUpComponent; }
	FORCEINLINE USkeletalMeshComponent* GetSkeletalMeshComponent() const { return SkeletalMeshComponent; }
	FORCEINLINE UTP_WeaponComponent* GetTP_WeaponComponent() const { return TP_WeaponComponent; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UTP_PickUpComponent* TP_PickUpComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMeshComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UTP_WeaponComponent* TP_WeaponComponent = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void RunPickUp(AShootingSystemCharacter* ShootingSystemCharacterParam);
};
