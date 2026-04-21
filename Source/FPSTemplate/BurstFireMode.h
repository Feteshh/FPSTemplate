// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireMode.h"
#include "BurstFireMode.generated.h"

UCLASS(EditInlineNew)
class FPSTEMPLATE_API UBurstFireMode : public UFireMode
{
	GENERATED_BODY()
	
public:
	virtual void Fire_Implementation() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BurstCount = 3;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BurstIntervalPercentage = 0.4f; // 40% of the time between each shot
	
private:
	int ShotsFired = 0;
	FTimerHandle BurstFireTimer;
	
	void FireNextShot();
};
