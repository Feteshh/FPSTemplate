// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UFaceCameraTextRenderComponent;
class UItemTextDisplay;

UENUM(BlueprintType)
enum class ERarity: uint8
{
	Common UMETA(DisplayName = "Common"),
	UnCommon UMETA(DisplayName = "UnCommon"),
	Rare UMETA(DisplayName = "Rare"),
	Epic UMETA(DisplayName = "Epic"),
	Legendary UMETA(DisplayName = "Legendary")
};

UENUM(BlueprintType)
enum class EItemType: uint8
{
	Gun UMETA(DisplayName = "Weapon"),
	Key UMETA(DisplayName = "Key"),
	Consumable UMETA(DisplayName = "Consumable"),
	Standard UMETA(DisplayName = "Standard")
};


USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERarity Rarity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> EquipActorClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight;
};

UCLASS()
class FPSTEMPLATE_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void InitializeItem(FDataTableRowHandle NewItemRow);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDataTableRowHandle ItemRow;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<ERarity,FColor> RarityColor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Model;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFaceCameraTextRenderComponent* ItemTextDisplay;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* Collider;
	
	
	
	
};
