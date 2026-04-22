// Fill out your copyright notice in the Description page of Project Settings.


#include "FireMode.h"
#include "TP_WeaponComponent.h"
#include "Kismet/GameplayStatics.h"

void UFireMode::Fire_Implementation()
{
	if (!Weapon || !Weapon->ShootingMethod) return;
	
	
}

void UFireMode::PlayFireSound()
{
	if (!Weapon || !Weapon->FireSound) return;
	
	UGameplayStatics::PlaySoundAtLocation(
		Weapon,
		Weapon->FireSound,
		Weapon->GetOwner()->GetActorLocation(),
		Weapon->FireSoundVolume);
}