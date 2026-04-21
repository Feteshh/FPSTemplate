// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleShotFireMode.h"
#include "ShootingMethod.h"
#include "TP_WeaponComponent.h"

void USingleShotFireMode::Fire_Implementation()
{
	Super::Fire_Implementation();
	
	FVector Start, Direction;
	Weapon->ComputeFireStartAndDirection(Start, Direction);
	
	Weapon->ShootingMethod->FireOneShot(Start, Direction);
}
