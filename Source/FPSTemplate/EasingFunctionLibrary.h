// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EasingFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FPSTEMPLATE_API UEasingFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float EaseInQuadratic(float T);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float EaseInCubic(float T);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float EaseOutQuadratic(float T);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float Elastic(float T, float H, int B);
};
