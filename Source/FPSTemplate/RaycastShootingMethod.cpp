// Fill out your copyright notice in the Description page of Project Settings.


#include "RaycastShootingMethod.h"
#include "DamageableInterface.h"
#include "EffectComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

void URaycastShootingMethod::FireSingle(const FVector& Start, const FVector& Direction)
{
	FVector End = Start + Direction * Range;
	
	FHitResult Hit;
	bool bHit = Trace(Start, End, Hit);
	
	SpawnBeamFX(Start, End, Hit, bHit);
	
	if (!bHit || !Hit.bBlockingHit) return;
	
	SpawnHitFX(Hit);
	
	AActor* HitActor = Hit.GetActor();
	if (!HitActor) return;
	
	//Deal Damage
	if (HitActor->Implements<UDamageableInterface>())
	{
		IDamageableInterface::Execute_ApplyDamage(HitActor, Weapon->Damage);
	}
	
	//Apply Effects
	if (UEffectComponent* Effects = HitActor->FindComponentByClass<UEffectComponent>())
	{
		for (const FWeaponEffect& Effect : Weapon->WeaponEffects)
		{
			Effects->ApplyEffect(
				Effect.Type,
				Effect.Magnitude,
				Effect.Duration,
				Effect.TickInterval,
				Effect.bStacks
				);
		}
	}
}

bool URaycastShootingMethod::Trace(const FVector& Start, const FVector& End, FHitResult& OutHit) const
{
	return Weapon->GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility);
}

void URaycastShootingMethod::SpawnBeamFX(const FVector& Start, const FVector& End, const FHitResult& Hit, bool isHit) const
{
	if (!BeamParticles) return;

	FVector BeamEnd = isHit ? Hit.ImpactPoint : End;

	if (UNiagaraComponent* Beam = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		Weapon->GetWorld(), BeamParticles, Start, (End - Start).Rotation()))
	{
		Beam->SetVariableVec3(TEXT("EndPoint"), BeamEnd);
	}
}

void URaycastShootingMethod::SpawnHitFX(const FHitResult& Hit) const
{
	if (!HitParticles) return;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		Weapon->GetWorld(), HitParticles, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}

