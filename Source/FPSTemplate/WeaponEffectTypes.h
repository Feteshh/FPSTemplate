#pragma once

#include "CoreMinimal.h"
#include "EffectType.h"
#include "WeaponEffectTypes.generated.h"

USTRUCT(BlueprintType)
struct FWeaponEffect
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEffectType Type = EEffectType::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Magnitude = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TickInterval = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bStacks = false;
};
