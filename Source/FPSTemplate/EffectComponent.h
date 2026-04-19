// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectType.h"
#include "Components/ActorComponent.h"
#include "EffectComponent.generated.h"


USTRUCT(BlueprintType)
struct FActiveEffect
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEffectType EffectType = EEffectType::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Magnitude = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TickInterval = 1.f;
	
	float TimeRemaining = 0.f;
	float TickTimer = 0.f;
	
	bool bStacks = false;
};


class UHealthComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSTEMPLATE_API UEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEffectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	UHealthComponent* HealthComponent;
	
	UPROPERTY()
	TArray<FActiveEffect> ActiveEffects;
	
public:
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffect(EEffectType Type, float Magnitude, float Duration, float TickInterval = 1.f, bool bStacks = false);
	
	UFUNCTION(BlueprintCallable)
	void RemoveEffect(EEffectType Type);
	
	UFUNCTION(BlueprintCallable)
	bool HasEffect(EEffectType Type) const;
	
private:
	void ProcessEffect(FActiveEffect& Effect, float DeltaTime);
	void ApplyEffectTick(const FActiveEffect& Effect);
	
		
};
