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
}

void ATP_WeaponPickUp::AttachWeapon(AFPSTemplateCharacter* PickUpCharacter)
{
}


