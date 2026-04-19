// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectComponent.h"

#include "HealthComponent.h"

// Sets default values for this component's properties
UEffectComponent::UEffectComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UEffectComponent::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent = GetOwner()->FindComponentByClass<UHealthComponent>();
}


// Called every frame
void UEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	for (int32 i = ActiveEffects.Num() - 1; i >= 0; i--)
	{
		FActiveEffect& Effect = ActiveEffects[i];
		ProcessEffect(Effect, DeltaTime);
		
		if (Effect.TimeRemaining <= 0.f)
		{
			ActiveEffects.RemoveAt(i);
		}
	}
}

void UEffectComponent::ApplyEffect(EEffectType Type, float Magnitude, float Duration, float TickInterval, bool bStacks)
{
	if (!bStacks)
	{
		for (FActiveEffect& Effect : ActiveEffects)
		{
			if (Effect.EffectType == Type)
			{
				Effect.Duration = Duration;
				Effect.TimeRemaining = Duration;
				Effect.Magnitude = Magnitude;
				return;
			}
		}
	}
	FActiveEffect NewEffect;
	NewEffect.EffectType = Type;
	NewEffect.Magnitude = Magnitude;
	NewEffect.Duration = Duration;
	NewEffect.TimeRemaining = Duration;
	NewEffect.TickInterval = TickInterval;
	NewEffect.bStacks = bStacks;
	
	ActiveEffects.Add(NewEffect);
}

void UEffectComponent::RemoveEffect(EEffectType Type)
{
	ActiveEffects.RemoveAll([&](const FActiveEffect& Effect)
	{
		return Effect.EffectType == Type;
	});
}

bool UEffectComponent::HasEffect(EEffectType Type) const
{
	for (const FActiveEffect& Effect : ActiveEffects)
	{
		if (Effect.EffectType == Type)
			return true;
	}
	return false;
}

void UEffectComponent::ProcessEffect(FActiveEffect& Effect, float DeltaTime)
{
	Effect.TimeRemaining -= DeltaTime;
	Effect.TickTimer += DeltaTime;
	
	if (Effect.TickTimer >= Effect.TickInterval)
	{
		Effect.TickTimer = 0.f;
		ApplyEffectTick(Effect);
	}
}

void UEffectComponent::ApplyEffectTick(const FActiveEffect& Effect)
{
	if (!HealthComponent) return;
	
	switch (Effect.EffectType)
	{
	case EEffectType::Poison:
	case EEffectType::Burn:
		HealthComponent->ApplyDamage(Effect.Magnitude);
		break;
	case EEffectType::HealOverTime:
		HealthComponent->ApplyHealing(Effect.Magnitude);
		break;
	case EEffectType::Slow:
		break;
		
	default:
		break;
	}
}
