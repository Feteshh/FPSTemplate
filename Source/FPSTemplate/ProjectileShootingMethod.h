// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSTemplateProjectile.h"
#include "ShootingMethod.h"
#include "ProjectileShootingMethod.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class FPSTEMPLATE_API UProjectileShootingMethod : public UShootingMethod
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<AFPSTemplateProjectile> ProjectileClass;
	
	virtual void FireSingle(const FVector& Start, const FVector& Direction) override;
};
