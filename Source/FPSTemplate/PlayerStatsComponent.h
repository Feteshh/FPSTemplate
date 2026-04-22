// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSTEMPLATE_API UPlayerStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseWalkSpeed = 500.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseJumpZ = 500.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentWalkSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentJumpZ;
	
	void ApplySpeedMultiplier(float Multiplier);
	void ApplyJumpMultiplier(float Multiplier);
	void ResetStats();
	
};
