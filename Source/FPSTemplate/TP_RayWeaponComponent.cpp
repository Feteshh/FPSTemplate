// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_RayWeaponComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "FPSTemplateCharacter.h"


void UTP_RayWeaponComponent::PerformFire()
{
	if (!Character) return;

	const APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	if (!PlayerController) return;

	const UWorld* const World = GetWorld();
	if (!World) return;
	
	FRotator CameraRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
	FVector Start = GetOwner()->GetActorLocation() + CameraRotation.RotateVector(MuzzleOffset);
	FVector Direction = CameraRotation.Vector();
	
	for (int i = 0; i < RayBounceAmount; i++)
	{
		FHitResult Hit;
		FVector End = Start + Direction * WeaponRange;
		
		bool bHit = TraceBeam(Start, End, Hit);
		
		SpawnBeamFX(Start, End, Hit, bHit);
		
		if (!bHit || !Hit.bBlockingHit)
			break;
		
		SpawnHitFX(Hit);
		ApplyPhysicsImpulse(Hit, Direction);
		
		Direction = ComputeBounceDirection(Direction, Hit);
		Start = Hit.ImpactPoint;
	}
}

bool UTP_RayWeaponComponent::TraceBeam(const FVector& Start, const FVector& End, FHitResult& OutHit) const
{
	return GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility);
}

void UTP_RayWeaponComponent::SpawnBeamFX(const FVector& Start, const FVector& End, const FHitResult& Hit,
	bool bHit) const
{
	if (!BeamParticles) return;
	
	FVector BeamEnd = bHit ? Hit.ImpactPoint : End;

	if (UNiagaraComponent* Beam = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), BeamParticles, Start, (End - Start).Rotation()))
		Beam->SetVariableVec3(TEXT("EndPoint"),BeamEnd);
}

void UTP_RayWeaponComponent::SpawnHitFX(const FHitResult& Hit) const
{
	if (!HitParticles) return;
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),HitParticles,Hit.ImpactPoint,Hit.ImpactNormal.Rotation());
}

void UTP_RayWeaponComponent::ApplyPhysicsImpulse(const FHitResult& Hit, const FVector& Direction)
{
	if (UPrimitiveComponent* Comp = Hit.GetComponent())
	{
		if (Comp->IsSimulatingPhysics())
			Comp->AddImpulseAtLocation(Direction * 300000.f, Hit.ImpactPoint);
	}
}

FVector UTP_RayWeaponComponent::ComputeBounceDirection(const FVector& IncomingDir, const FHitResult& Hit)
{
	FRotator BounceRotation = Hit.ImpactNormal.Rotation();
	return BounceRotation.RotateVector(IncomingDir);
}
