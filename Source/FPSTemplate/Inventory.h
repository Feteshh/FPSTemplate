// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"


USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()
	
public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle ItemRow;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Quantity = 0;
	
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSTEMPLATE_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
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
	
	void EquipSelectedItem();
	
	
};
