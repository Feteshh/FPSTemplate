#pragma once

#include "CoreMinimal.h"
#include "TP_WeaponComponent.h"
#include "ShootingMethod.generated.h"
class UShootingPattern;

UCLASS(ABSTRACT, Blueprintable,BlueprintType, EditInlineNew, DefaultToInstanced)
class FPSTEMPLATE_API UShootingMethod : public UObject
{
	GENERATED_BODY()
	
	
	
public:
	UPROPERTY()
	UTP_WeaponComponent* Weapon;
	
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Pattern")
	UShootingPattern* ShootingPattern;
	
	virtual void Initialize(UTP_WeaponComponent* InWeapon)
	{
		Weapon = InWeapon;
	}
	
	UFUNCTION(BlueprintNativeEvent)
	void FireOneShot(const FVector& Start, const FVector& Direction);
	
	UFUNCTION()
	virtual void FireSingle(const FVector& Start, const FVector& Direction);
};
