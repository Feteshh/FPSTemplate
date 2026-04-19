// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_WeaponComponent.h"
#include "NiagaraComponent.h"

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
	
	UPROPERTY(EditAnywhere,Category = Weapon,meta = (ClampMin = "1"))
	int RayBounceAmount = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Asset Refrences")
	UNiagaraSystem* BeamParticles;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset Refrences")
	UNiagaraSystem* HitParticles;
	
	virtual void PerformFire() override;
	
private:
	bool TraceBeam(const FVector& Start,const FVector& End, FHitResult& OutHit) const;
	void SpawnBeamFX(const FVector& Start, const FVector& End, const FHitResult& Hit, bool bHit) const;
	void SpawnHitFX(const FHitResult& Hit) const;
	static void ApplyPhysicsImpulse(const FHitResult& Hit, const FVector& Direction);
	static FVector ComputeBounceDirection(const FVector& IncomingDir, const FHitResult& Hit);
};
