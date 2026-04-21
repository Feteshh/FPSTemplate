// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ShootingPattern.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew, Blueprintable, BlueprintType)
class FPSTEMPLATE_API UShootingPattern : public UObject
{
	GENERATED_BODY()

public:
	virtual TArray<FVector> GenerateDirections(const FVector& Directions) PURE_VIRTUAL(UShootingPattern::GenerateDirections, return {};);
	
};
