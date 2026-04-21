// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShootingPattern.h"
#include "ShotgunPattern.generated.h"

/**
 * 
 */
UCLASS()
class FPSTEMPLATE_API UShotgunPattern : public UShootingPattern
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	int PelletCount = 8;
	
	UPROPERTY(EditAnywhere)
	float SpreadAngle = 5.f;
	
	virtual TArray<FVector> GenerateDirections(const FVector& Forward) override;
};
