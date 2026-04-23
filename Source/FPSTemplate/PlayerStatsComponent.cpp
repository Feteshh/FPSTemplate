// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatsComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UPlayerStatsComponent::UPlayerStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	// ...
}

void UPlayerStatsComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		BaseWalkSpeed = Character->GetCharacterMovement()->MaxWalkSpeed;
		BaseJumpZ = Character->GetCharacterMovement()->JumpZVelocity;
	}
}


void UPlayerStatsComponent::ApplySpeedMultiplier(float Multiplier)
{
	if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		float NewSpeed = BaseWalkSpeed * Multiplier;
		Character->GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
		
		UE_LOG(LogTemp, Warning, TEXT("[Stats] Speed Boost Applied: %f -> %f"), BaseWalkSpeed, NewSpeed);
	}
}

void UPlayerStatsComponent::ApplyJumpMultiplier(float Multiplier)
{
	if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		float NewJumpZ = BaseJumpZ * Multiplier;
		Character->GetCharacterMovement()->JumpZVelocity = NewJumpZ;
		
		UE_LOG(LogTemp, Warning, TEXT("[Stats] Speed Boost Applied: %f -> %f"), BaseJumpZ, NewJumpZ);
    
	}
}

void UPlayerStatsComponent::ResetSpeed()
{
	if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	}
}

void UPlayerStatsComponent::ResetJumpBoost()
{
	if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		Character->GetCharacterMovement()->JumpZVelocity = BaseJumpZ;
	}
}

void UPlayerStatsComponent::ResetStats()
{
	ResetSpeed();
	ResetJumpBoost();
}
