// Fill out your copyright notice in the Description page of Project Settings.


#include "FireMode.h"
#include "TP_WeaponComponent.h"

void UFireMode::Fire_Implementation()
{
	if (!Weapon || !Weapon->ShootingMethod) return;
}
