// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FireMode.generated.h"

class UTP_WeaponComponent;

UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class FPSTEMPLATE_API UFireMode : public UObject
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY()
	UTP_WeaponComponent* Weapon;
	
	
	virtual void Initialize(UTP_WeaponComponent* InWeapon)
	{
		Weapon = InWeapon;
	}
	
	UFUNCTION(BlueprintNativeEvent)
	void Fire();
	void PlayFireSound();
};
