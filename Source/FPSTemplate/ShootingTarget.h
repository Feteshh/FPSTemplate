// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageableInterface.h"
#include "EffectComponent.h"
#include "GameFramework/Actor.h"
#include "ShootingTarget.generated.h"

UCLASS()
class FPSTEMPLATE_API AShootingTarget : public AActor, public IDamageableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShootingTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHealthComponent* Health;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UEffectComponent* Effects;
	
	FVector InitialLocation;
	FRotator InitialRotation;
	
public:	
	// Called every frame
	virtual void ApplyDamage_Implementation(float Amount) override;

private:
	UFUNCTION()
	void OnDeath();
};
