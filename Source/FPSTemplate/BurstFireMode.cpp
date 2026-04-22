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
		// gets a new duration that is a percentage of FireRate to shoot all bursts in
		float TotalBurstDuration = Weapon->FireRate * BurstIntervalPercentage; 
		
		float Interval = TotalBurstDuration / (BurstCount - 1);
		
		Weapon->GetWorld()->GetTimerManager().SetTimer(BurstFireTimer,this,&UBurstFireMode::FireNextShot,Interval,false);
	}
}
