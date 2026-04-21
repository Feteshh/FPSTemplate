// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileShootingMethod.h"

void UProjectileShootingMethod::FireSingle(const FVector& Start, const FVector& Direction)
{
	
	if (!ProjectileClass || !Weapon) return;

	UWorld* World = Weapon->GetWorld();
	if (!World) return;
	
	const FRotator SpawnRotation = Direction.Rotation();
	
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
	AFPSTemplateProjectile* Projectile = World->SpawnActor<AFPSTemplateProjectile>(ProjectileClass,Start, SpawnRotation, Params);
	
	if (!Projectile) return;
	
	Projectile->Damage = Weapon->Damage;
	Projectile->Effects = Weapon->WeaponEffects;
	
}
