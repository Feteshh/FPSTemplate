// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

#include "FPSTemplateCharacter.h"
#include "Item.h"
#include "TP_WeaponComponent.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	InventorySlots.SetNum(10);
	
	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventory::AddItem(FDataTableRowHandle ItemRow)
{
	if (!ItemRow.DataTable)
		return false;
	
	FItemData* ItemData = ItemRow.GetRow<FItemData>("AddItem");
	
	if (!ItemData)
		return false;
	
	if (ItemData->bStackable)
	{
		for (FInventorySlot& Slot : InventorySlots)
		{
			if (Slot.ItemRow == ItemRow &&
				Slot.Quantity < ItemData->MaxStackSize)
			{
				Slot.Quantity++;
				return true;
			}
		}
	}
	
	for (FInventorySlot& Slot : InventorySlots)
	{
		if (Slot.Quantity == 0)
		{
			Slot.ItemRow = ItemRow;
			Slot.Quantity = 1;
			
			return true;
		}
	}
	return false;
}

void UInventory::SelectSlot(int NewIndex)
{
	if (NewIndex < 0)
	{
		SelectedSlotIndex = InventorySlots.Num() - 1;
		return;
	}
	else if (NewIndex >= InventorySlots.Num())
	{
		SelectedSlotIndex = 0;
	}
	else 
		SelectedSlotIndex = FMath::Clamp(NewIndex, 0, InventorySlots.Num() - 1);
}

FString UInventory::GetItemNameFromSlot(const FInventorySlot& Slot)
{
	if (!Slot.ItemRow.DataTable)
		return "Empty";
	
	FItemData* ItemData = Slot.ItemRow.GetRow<FItemData>("GetItemName");
	
	if (!ItemData)
		return "Invalid";
	
	return ItemData->ItemName;
}

int UInventory::GetItemQuantity(const FInventorySlot& Slot)
{
	if (!Slot.ItemRow.DataTable)
		return 0;
	
	FItemData* ItemData = Slot.ItemRow.GetRow<FItemData>("GetItemQuantity");
	
	if (!ItemData)
		return -1;
	
	return Slot.Quantity;
}

void UInventory::EquipSelectedItem()
{
	if (EquippedActor) // Destroys current equipped item
	{
		EquippedActor->Destroy();
		EquippedActor = nullptr;
	}
	
	if (!InventorySlots.IsValidIndex(SelectedSlotIndex))
		return;
	
	FInventorySlot& Slot = InventorySlots[SelectedSlotIndex];
	if (Slot.Quantity <= 0)
		return;
	
	FItemData* ItemData = Slot.ItemRow.GetRow<FItemData>("EquipSelectedItem");
	if (!ItemData)
		return;
	
	if (!ItemData->EquipActorClass)
		return;
	
	AActor* OwnerActor = GetOwner();
	if (!OwnerActor)
		return;
	
	AFPSTemplateCharacter* Character = Cast<AFPSTemplateCharacter>(OwnerActor);
	if (!Character)
		return;
	
	EquippedActor = GetWorld()->SpawnActor<AActor>(ItemData->EquipActorClass);
	if (!EquippedActor) 
		return;
	
	EquippedActor->AttachToComponent(Character->GetMesh1P(),FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("GripPoint"));
	
	if (UTP_WeaponComponent* WeaponComponent = EquippedActor->FindComponentByClass<UTP_WeaponComponent>())
	{
		WeaponComponent->AttachWeapon(Character);
	}
}

void UInventory::CheckCurrentSlot(const FInventorySlot& Slot)
{
	if (InventorySlots.IsValidIndex(SelectedSlotIndex))
	{
		if (&InventorySlots[SelectedSlotIndex] == &Slot)
		{
			SelectSlot(SelectedSlotIndex);
		}
	}
}






