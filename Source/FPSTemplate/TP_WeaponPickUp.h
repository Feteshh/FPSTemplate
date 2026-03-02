// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TP_WeaponComponent.h"
#include "FPSTemplateCharacter.h"
#include "TP_PickUpComponent.h"
#include "TP_WeaponPickUp.generated.h"

UCLASS()
class FPSTEMPLATE_API ATP_WeaponPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATP_WeaponPickUp();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = GamePlay)
	UTP_PickUpComponent* PickUpComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Weapon)
	UTP_WeaponComponent* WeaponPickUp;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION() void AttachWeapon(AFPSTemplateCharacter* PickUpCharacter);
	
	
};
