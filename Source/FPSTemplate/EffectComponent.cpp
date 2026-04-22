// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectComponent.h"

#include "HealthComponent.h"
#include "PipelineFileCache.h"
#include "PlayerStatsComponent.h"
#include "DSP/AudioDebuggingUtilities.h"

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
			OnEffectExpired(Effect);
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
	
	AActor* Owner = GetOwner();
	
	if (Type == EEffectType::SpeedBoost)
	{
		if (UPlayerStatsComponent* Stats = Owner->FindComponentByClass<UPlayerStatsComponent>())
		{
			Stats->ApplySpeedMultiplier(Magnitude);
		}
	}
	if (Type == EEffectType::HighJump)
	{
		if (UPlayerStatsComponent* Stats = Owner->FindComponentByClass<UPlayerStatsComponent>())
		{
			Stats->ApplyJumpMultiplier(Magnitude);
		}
	}
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

void UEffectComponent::RemoveAllEffects()
{
	ActiveEffects.Empty();
	
	if (UMeshComponent* Mesh = GetOwner()->FindComponentByClass<UMeshComponent>())
	{
		Mesh->SetVectorParameterValueOnMaterials("TintColor", FVector(0,0,0));
	}
	
	GetOwner()->SetActorScale3D(FVector(1,1,1));
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
	
	AActor* Owner = GetOwner();
	UMeshComponent* Mesh = GetOwner()->FindComponentByClass<UMeshComponent>();
	
	switch (Effect.EffectType)
	{
		
	case EEffectType::Poison:
		HealthComponent->ApplyDamage(Effect.Magnitude);
		if (Mesh) Mesh->SetVectorParameterValueOnMaterials("TintColor", FVector(0,1,0));
		break;
	
	case EEffectType::Burn:
		HealthComponent->ApplyDamage(Effect.Magnitude);
		if (Mesh) Mesh->SetVectorParameterValueOnMaterials("TintColor", FVector(1,0,0));
		break;
		
	case EEffectType::HealOverTime:
		HealthComponent->ApplyHealing(Effect.Magnitude);
		break;
	
	case EEffectType::Heal:
		HealthComponent->ApplyHealing(Effect.Magnitude);
		break;
		
	case EEffectType::ClearDebuff:
		RemoveAllEffects();
		break;
		
	case EEffectType::IncreaseSize:
		if (Owner)
		{
			FVector Scale = Owner->GetActorScale3D() + FVector(Effect.Magnitude);
			Owner->SetActorScale3D(Scale);
		}
		break;
	default:
		break;
	}
}

void UEffectComponent::OnEffectExpired(const FActiveEffect& Effect)
{
	AActor* Owner = GetOwner();
	UMeshComponent* Mesh = GetOwner()->FindComponentByClass<UMeshComponent>();
	
	switch (Effect.EffectType)
	{
		case EEffectType::Poison:
		case EEffectType::Burn:
		if (Mesh) Mesh->SetVectorParameterValueOnMaterials("TintColor", FVector(0,0,0));
		break;
		
	case EEffectType::IncreaseSize:
		Owner->SetActorScale3D(FVector(1,1,1));
		break;
		
	case EEffectType::SpeedBoost:
	case EEffectType::HighJump:
		if (UPlayerStatsComponent* Stats = Owner->FindComponentByClass<UPlayerStatsComponent>())
		{
			Stats->ResetStats();
		}
		break;
	default:
		break;
	}
}
