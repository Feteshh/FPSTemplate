// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_WeaponPickUp.h"

// Sets default values
ATP_WeaponPickUp::ATP_WeaponPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATP_WeaponPickUp::BeginPlay()
{
	Super::BeginPlay();
	PickUpComponent = FindComponentByClass<UTP_PickUpComponent>();
	
	if (PickUpComponent != nullptr)
	{
		WeaponPickUp = FindComponentByClass<UTP_WeaponComponent>();
		if (WeaponPickUp != nullptr)
		{
			PickUpComponent->OnPickUp.AddDynamic(this,&ATP_WeaponPickUp::AttachWeapon);
		}
	}
	
}

void ATP_WeaponPickUp::AttachWeapon(AFPSTemplateCharacter* PickUpCharacter)
{
	if (WeaponPickUp != nullptr)
	{
		if (PickUpCharacter != nullptr)
		{
			WeaponPickUp->AttachWeapon(PickUpCharacter);
		}
	}
}


