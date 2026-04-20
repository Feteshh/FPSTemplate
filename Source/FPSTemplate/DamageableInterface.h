// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "DamageableInterface.generated.h"


UINTERFACE(MinimalAPI, Blueprintable)
class UDamageableInterface : public UInterface
{
	GENERATED_BODY()
};

class IDamageableInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
	void ApplyDamage(float Amount);
};

