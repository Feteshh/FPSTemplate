// Fill out your copyright notice in the Description page of Project Settings.


#include "ShotgunPattern.h"

TArray<FVector> UShotgunPattern::GenerateDirections(const FVector& Forward)
{
	TArray<FVector> DirectionsArray;
	
	for (int i = 0; i < PelletCount; i ++)
	{
		FRotator SpreadRot(
			FMath::RandRange(-SpreadAngle, SpreadAngle),
			FMath::RandRange(-SpreadAngle, SpreadAngle),
			0);
		DirectionsArray.Add(SpreadRot.RotateVector(Forward));
	}
	return DirectionsArray;
}