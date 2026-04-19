// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "TP_WeaponComponent.h"
#include "TP_ShotgunWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class FPSTEMPLATE_API UTP_ShotgunWeaponComponent : public UTP_WeaponComponent
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Shotgun")
	int32 PelletCount = 8;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Shotgun")
	float SpreadAngle = 4.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Shotgun")
	float WeaponRange = 5000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Shotgun")
	UNiagaraSystem* BeamParticles;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Shotgun")
	UNiagaraSystem* HitParticles;
	
	virtual void PerformFire() override;
	
private:
	bool TracePellet(const FVector& Start,const FVector& End, FHitResult& OutHit) const;
	void SpawnPelletBeam(const FVector& Start, const FVector& End, const FHitResult& Hit, bool bHit) const;
	void SpawnPelletHitFX(const FHitResult& Hit) const;
	void ApplyPhysicsImpulse(const FHitResult& Hit, const FVector& Direction) const;
};
