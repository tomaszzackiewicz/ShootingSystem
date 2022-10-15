// Fill out your copyright notice in the Description page of Project Settings.


#include "Other/Gun.h"
#include "Components/TP_PickUpComponent.h"
#include "Shared/StaticGlobalProperties.h"
#include "Components/TP_WeaponComponent.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TP_PickUpComponent = CreateDefaultSubobject<UTP_PickUpComponent>(TEXT("TP_PickUpComponent"));
	RootComponent = TP_PickUpComponent;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);

	TP_WeaponComponent = CreateDefaultSubobject<UTP_WeaponComponent>(TEXT("TP_WeaponComponent"));
	
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	if (TP_PickUpComponent)
	{
		TP_PickUpComponent->OnPickUp.AddDynamic(this, &AGun::RunPickUp);
	}
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::RunPickUp(AShootingSystemCharacter* ShootingSystemCharacterParam)
{

	if (TP_WeaponComponent)
	{
		
		TP_WeaponComponent->AttachWeapon(ShootingSystemCharacterParam);
	}
}

void AGun::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (TP_PickUpComponent)
	{
		// Unregister from the OnUseItem Event
		TP_PickUpComponent->OnPickUp.RemoveDynamic(this, &AGun::RunPickUp);
	}
}
