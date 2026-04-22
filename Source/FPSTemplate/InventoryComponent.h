// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class AFPSTemplateCharacter;

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle ItemRow;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Quantity = 0;
	
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSTEMPLATE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AItem> BaseItem;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInventorySlot> InventorySlots;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SelectedSlotIndex = 0;
	
	UPROPERTY()
	AActor* EquippedActor;
	
	UFUNCTION(BlueprintCallable)
	bool AddItem(FDataTableRowHandle ItemRow);
	
	UFUNCTION(BlueprintCallable)
	void SelectSlot(int NewIndex);
	
	UFUNCTION(BlueprintCallable)
	FString GetItemNameFromSlot(const FInventorySlot& Slot);
	
	UFUNCTION(blueprintCallable)
	int GetItemQuantity(const FInventorySlot& Slot);
	
	UFUNCTION(BlueprintCallable)
	bool HasItem(FName RowName) const;
	
	void EquipActorItem(const FItemData& ItemData, AFPSTemplateCharacter* Character);

	void ApplyConsumableEffect(const FItemData* ItemData, AFPSTemplateCharacter* Character);
	void RemoveOneFromSlot(int32 INT32);
	UFUNCTION(BlueprintCallable)
	void EquipSelectedItem();
	
	void CheckCurrentSlot(const FInventorySlot& Slot);
	
	UFUNCTION(BlueprintCallable)
	void DropItem();
	void UseSelectedItem();
};
