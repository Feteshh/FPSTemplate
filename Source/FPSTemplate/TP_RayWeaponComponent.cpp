// Fill out your copyright notice in the Description page of Project Settings.


#include "TP_RayWeaponComponent.h"
#include "FPSTemplateCharacter.h"

void UTP_RayWeaponComponent::Fire()
{
	Super::Fire();
	
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
		if (PlayerController != nullptr)
		{
			FHitResult OutHit;
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			//MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector Start = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
			const FVector Forward = SpawnRotation.Vector();
			const FVector End = Start + (Forward * WeaponRange);
			
			bool isHit = World->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility);
			DrawDebugLine(GetWorld(),Start,End,FColor::Yellow,false,1,0,1);
			
			if (isHit)
			{
				if (OutHit.bBlockingHit)
				{
					AActor* OtherActor = OutHit.GetActor();
					UPrimitiveComponent* OtherComponent = OutHit.GetComponent();
					
					if (OtherActor != nullptr &&
						OtherActor != GetOwner() &&
						OtherComponent != nullptr &&
						OtherComponent->IsSimulatingPhysics())
					{
						OtherComponent->AddImpulseAtLocation(Forward * 300000.f,OutHit.ImpactPoint);
					}
				}
			}
			
		}
	}
}
