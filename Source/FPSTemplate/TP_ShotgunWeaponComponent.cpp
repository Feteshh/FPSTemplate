// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_ShotgunWeaponComponent.h"

#include "FPSTemplateCharacter.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"


void UTP_ShotgunWeaponComponent::PerformFire()
{
	if (!Character) return;
	APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	if (!PlayerController) return;
	
	UWorld* World = PlayerController->GetWorld();
	if (!World) return;
	
	FRotator CamRot = PlayerController->PlayerCameraManager->GetCameraRotation();
	FVector Start = GetOwner()->GetActorLocation() + CamRot.RotateVector(MuzzleOffset);
	
	for (int i = 0; i < PelletCount; i++)
	{
		FRotator PelletRot = CamRot;
		PelletRot.Yaw += FMath::RandRange(-SpreadAngle, SpreadAngle);
		PelletRot.Pitch += FMath::RandRange(-SpreadAngle, SpreadAngle);
		
		FVector Direction = PelletRot.Vector();
		FVector End = Start + Direction * WeaponRange;
		
		FHitResult Hit;
		bool bHit = TracePellet(Start, End, Hit);
		
		SpawnPelletBeam(Start, End,Hit, bHit);
		
		if (bHit && Hit.bBlockingHit)
		{
			SpawnPelletHitFX(Hit);
			ApplyPhysicsImpulse(Hit, Direction);
		}
	}
}

bool UTP_ShotgunWeaponComponent::TracePellet(const FVector& Start, const FVector& End, FHitResult& OutHit) const
{
	return GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility);
}

void UTP_ShotgunWeaponComponent::SpawnPelletBeam(const FVector& Start, const FVector& End, const FHitResult& Hit, bool bHit) const
{
	if (!BeamParticles) return;
	
	FVector BeamEnd = bHit ? Hit.ImpactPoint : End;
	
	if (UNiagaraComponent* Beam = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),BeamParticles,Start,(End - Start).Rotation()))
			Beam->SetVariableVec3(TEXT("EndPoint"),BeamEnd);
	
}

void UTP_ShotgunWeaponComponent::SpawnPelletHitFX(const FHitResult& Hit) const
{
	if (!HitParticles) return;
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),HitParticles,Hit.ImpactPoint,Hit.ImpactPoint.Rotation());
}

void UTP_ShotgunWeaponComponent::ApplyPhysicsImpulse(const FHitResult& Hit, const FVector& Direction) const
{
	if (UPrimitiveComponent* Comp = Hit.GetComponent())
	{
		if (Comp->IsSimulatingPhysics())
			Comp->AddImpulseAtLocation(Direction * 50000.f, Hit.ImpactPoint);
	}
}
