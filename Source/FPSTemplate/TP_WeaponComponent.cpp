// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"

#include "EnhancedInputComponent.h"
#include "FPSTemplateCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "FireMode.h"
#include "ShootingMethod.h"
#include "Animation/AnimInstance.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	FireSoundVolume = 0.6;
}

void UTP_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (ShootingMethod)
		ShootingMethod->Initialize(this);
	
	if (FireMode)
		FireMode->Initialize(this);
}

void UTP_WeaponComponent::AttachWeapon(AFPSTemplateCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	if (!Character)
	{
		return;
	}

	APlayerController* PC = Cast<APlayerController>(Character->GetController());
	if (!PC)
	{
		return;
	}

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PC->InputComponent);
	if (!EIC)
	{
		return;
	}

	if (!FireAction)
	{
		return;
	}
	

	EIC->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);
	EIC->BindAction(FireAction, ETriggerEvent::Started, this, &UTP_WeaponComponent::StartFiring);
	EIC->BindAction(FireAction, ETriggerEvent::Completed, this, &UTP_WeaponComponent::StopFiring);
}


void UTP_WeaponComponent::ComputeFireStartAndDirection(FVector& OutStart, FVector& OutDirection)
{
	if (!Character) return;
	
	APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	if (!PlayerController) return;
	
	FRotator CameraRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
	OutDirection = CameraRotation.Vector();
	OutStart = Character->GetActorLocation() + CameraRotation.RotateVector(MuzzleOffset);
}

void UTP_WeaponComponent::Fire()
{
	
	if (!FireMode)
		return;
	
	TryFire();
}

void UTP_WeaponComponent::StartFiring()
{
	bIsHoldingTrigger = true;
	TryFire();
}

void UTP_WeaponComponent::StopFiring()
{
	bIsHoldingTrigger = false;
}

void UTP_WeaponComponent::TryFire()
{
	if (!CanFire || !FireMode) return;
	
	FireMode->Fire();
	
	CanFire = false;
	
	GetWorld()->GetTimerManager().SetTimer(FireRateTimer, this, &UTP_WeaponComponent::ResetCanFire, FireRate, false);
	

}

void UTP_WeaponComponent::ResetCanFire()
{
	CanFire = true;
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}



