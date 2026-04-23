// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "ShootingMethod.h"
#include "RaycastShootingMethod.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, EditInlineNew)
class FPSTEMPLATE_API URaycastShootingMethod : public UShootingMethod
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Raycast")
	float Range = 10000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Raycast")
	UNiagaraSystem* BeamParticles;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Raycast")
	UNiagaraSystem* HitParticles;
	
	virtual void FireSingle(const FVector& Start, const FVector& Direction) override;
	
private:
	bool Trace(const FVector& Start,const FVector& End, FHitResult& OutHit) const;
	void SpawnBeamFX(const FVector& Start, const FVector& End, const FHitResult& Hit, bool isHit) const;
	void SpawnHitFX(const FHitResult& Hit) const;
	void ApplyPhysicsImpulse(const FHitResult& Hit, const FVector& Direction) const;
};
