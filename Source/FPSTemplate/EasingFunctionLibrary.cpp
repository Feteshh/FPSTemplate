// Fill out your copyright notice in the Description page of Project Settings.


#include "EasingFunctionLibrary.h"

float UEasingFunctionLibrary::EaseInQuadratic(float T)
{
	return FMath::Pow(T, 2);
}

float UEasingFunctionLibrary::EaseInCubic(float T)
{
	return FMath::Pow(T, 3);
}

float UEasingFunctionLibrary::EaseOutQuadratic(float T)
{
	return 1-(1 - T) * T;
}
float UEasingFunctionLibrary::Elastic(float T, float H, int B)
{
	return T * T - H * T * FMath::Sin(B*T * PI);
}