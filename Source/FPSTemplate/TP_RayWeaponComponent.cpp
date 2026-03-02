// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_RayWeaponComponent.h"

#include <string>

#include "FPSTemplateCharacter.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"
#include "SNegativeActionButton.h"

void UTP_RayWeaponComponent::Fire()
{
	Super::Fire();
	
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
		if (PlayerController != nullptr)
		{
			int currentRayBounce = 0;
			
			FHitResult OutHit;
			
			FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			//MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			FVector Start = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
			FVector Forward = SpawnRotation.Vector();
			FVector End = Start + (Forward * WeaponRange);
			
			while (currentRayBounce < RayBounceAmount)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, std::to_string(currentRayBounce).c_str());

				bool isHit = World->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility);
				FVector BeamEnd = End;
			
				if (BeamParticles != nullptr)
				{
					UNiagaraComponent* effect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),BeamParticles,Start,OutHit.ImpactNormal.Rotation());
					if (effect != nullptr)
					{
						effect->SetVariableVec3(TEXT("EndPoint"),BeamEnd);
					}
				}
			
			
				if (isHit)
				{
					if (OutHit.bBlockingHit)
					{
						if (HitParticles != nullptr)
						{
							UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),HitParticles,OutHit.ImpactPoint, OutHit.ImpactNormal.Rotation());
						}
						AActor* OtherActor = OutHit.GetActor();
						UPrimitiveComponent* OtherComponent = OutHit.GetComponent();
					
					
						if (OtherActor != nullptr &&
							OtherActor != GetOwner() &&
							OtherComponent != nullptr &&
							OtherComponent->IsSimulatingPhysics())
						{
							BeamEnd = OutHit.ImpactPoint;
							OtherComponent->AddImpulseAtLocation(Forward * 300000.f,OutHit.ImpactPoint);
						}
					
						SpawnRotation = OutHit.ImpactNormal.Rotation();
						Start = OutHit.ImpactPoint;
						Forward = SpawnRotation.RotateVector(Forward);
						End = Start + (Forward * WeaponRange);
					
						currentRayBounce++;
					}
				}
				else
				{
					currentRayBounce = RayBounceAmount;
				}
			}
		}
	}
}
