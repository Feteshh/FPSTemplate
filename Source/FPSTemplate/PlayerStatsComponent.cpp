// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatsComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UPlayerStatsComponent::UPlayerStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}







void UPlayerStatsComponent::ApplySpeedMultiplier(float Multiplier)
{
	CurrentWalkSpeed = BaseWalkSpeed;
	
	if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = CurrentWalkSpeed;
	}
}

void UPlayerStatsComponent::ApplyJumpMultiplier(float Multiplier)
{
	CurrentJumpZ = BaseJumpZ * Multiplier;
	
	if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		Character->GetCharacterMovement()->JumpZVelocity= CurrentJumpZ;
	}
}

void UPlayerStatsComponent::ResetStats()
{
	ApplyJumpMultiplier(1.f);
	ApplySpeedMultiplier(1.f);
}
