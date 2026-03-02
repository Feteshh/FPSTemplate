// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_WeaponComponent.h"
#include "TP_RayWeaponComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType,ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FPSTEMPLATE_API UTP_RayWeaponComponent : public UTP_WeaponComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = Weapon)
	float WeaponRange = 10000.f;
	
	virtual void Fire() override;
};
