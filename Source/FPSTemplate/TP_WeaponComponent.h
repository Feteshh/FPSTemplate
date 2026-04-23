
#pragma once

#include "CoreMinimal.h"
#include "WeaponEffectTypes.h"
#include "Components/ActorComponent.h"
#include "TP_WeaponComponent.generated.h"

class AFPSTemplateCharacter;
class UFireMode;
class UInputAction;
class UShootingMethod;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSTEMPLATE_API UTP_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Weapon", meta = (ClampMin = "0.02"))
	float FireRate = 0.1f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Weapon")
	bool CanFire = true;
	
	FTimerHandle FireRateTimer;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USoundBase* FireSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float FireSoundVolume;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FVector MuzzleOffset = FVector (100.f,0.f,10.f);

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* FireMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* FireAction;
	
	AFPSTemplateCharacter* Character;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Damage", meta = (ClampMin = "0"))
	float Damage = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Effects")
	TArray<FWeaponEffect> WeaponEffects;

	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Weapon|Shooting")
	UShootingMethod* ShootingMethod;
	
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Weapon|FireMode")
	UFireMode* FireMode;
	
	bool IsHoldingTrigger = false;

public:
	UTP_WeaponComponent();

	UFUNCTION(BlueprintCallable)
	void AttachWeapon(AFPSTemplateCharacter* TargetCharacter);
	
	UFUNCTION(BlueprintCallable)
	virtual void Fire();

	void StartFiring();
	void StopFiring();
	
	void TryFire();
	
	void ComputeFireStartAndDirection(FVector& OutStart, FVector& OutDirection);
	
protected:
	virtual void BeginPlay() override;
	void ResetCanFire();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
