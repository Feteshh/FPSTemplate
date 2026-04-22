// Fill out your copyright notice in the Description page of Project Settings.


#include "ShotgunPattern.h"

TArray<FVector> UShotgunPattern::GenerateDirections(const FVector& Forward)
{
	TArray<FVector> DirectionsArray;
	
	const FRotator BaseRotation = Forward.Rotation();
	
	for (int i = 0; i < PelletCount; i ++)
	{
		float Angle = FMath::RandRange(0.f, 360.f);
		float Radius = FMath::RandRange(0.f, SpreadAngle);
		
		float PitchOffset = FMath::Sin(FMath::DegreesToRadians(Angle)) * Radius;
		float YawOffset = FMath::Cos(FMath::DegreesToRadians(Angle)) * Radius;
		
		FRotator SpreadRotation = BaseRotation;
		SpreadRotation.Pitch += PitchOffset;
		SpreadRotation.Yaw += YawOffset;
		
		FVector ShotDirection = SpreadRotation.Vector();
		
		DirectionsArray.Add(ShotDirection);
		
		UE_LOG(LogTemp, Warning, TEXT("DirectionsArray[%d]"), i);
	}
	return DirectionsArray;
}