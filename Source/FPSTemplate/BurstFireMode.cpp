// Fill out your copyright notice in the Description page of Project Settings.


#include "BurstFireMode.h"
#include "ShootingMethod.h"
#include "TP_WeaponComponent.h"

void UBurstFireMode::Fire_Implementation()
{
	Super::Fire_Implementation();
	
	ShotsFired = 0;
	FireNextShot();
}

void UBurstFireMode::FireNextShot()
{
	if (ShotsFired >= BurstCount) return;
	
	FVector Start, Direction; 

	Weapon->ComputeFireStartAndDirection(Start, Direction);
	
	Weapon->ShootingMethod->FireOneShot(Start, Direction);
	
	ShotsFired++;
	
	if (ShotsFired < BurstCount)
	{
		float Interval = Weapon->FireRate * BurstIntervalPercentage;
		
		Weapon->GetWorld()->GetTimerManager().SetTimer(BurstFireTimer,this,&UBurstFireMode::FireNextShot,Interval,false);
	}
}
