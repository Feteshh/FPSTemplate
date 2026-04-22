// Fill out your copyright notice in the Description page of Project Settings.


#include "HorizonalShootingPattern.h"

TArray<FVector> UHorizonalShootingPattern::GenerateDirections(const FVector& Forward)
{
	TArray<FVector> Directions;
	
	const FRotator BaseRotation = Forward.Rotation();
	
	if (PelletCount <= 1)
	{
		Directions.Add(Forward);
		return Directions;
	}
	
	const float TotalSpread = SpreadAngle * 2.f;
	
	const float PelletGap = TotalSpread / (PelletCount - 1);
	
	for (int i = 0; i < PelletCount; i++)
	{
		float YawOffset = -SpreadAngle + (PelletGap * i);
		
		FRotator SpreadRotation = BaseRotation;
		SpreadRotation.Yaw += YawOffset;
		
		Directions.Add(SpreadRotation.Vector());
	}
	return Directions;
}
