// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	
}

void UHealthComponent::ApplyDamage(float Amount)
{
	if (Amount <= 0.f || IsDead()) return;
	
	CurrentHealth = FMath::Clamp(CurrentHealth - Amount, 0.f, MaxHealth);
	
	BroadcastHealthChanged();
	
	if (CurrentHealth <= 0.f)
	{
		HandleDeath();
	}
}

void UHealthComponent::ApplyHealing(float Amount)
{
	if (Amount <= 0.f || IsDead()) return;
	
	CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0.f, MaxHealth);
	
	BroadcastHealthChanged();
}


void UHealthComponent::BroadcastHealthChanged()
{
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
}

void UHealthComponent::HandleDeath()
{
	OnDeath.Broadcast();
}
