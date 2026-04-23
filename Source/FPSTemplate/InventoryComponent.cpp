// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "EffectComponent.h"
#include "FPSTemplateCharacter.h"
#include "Item.h"
#include "TP_WeaponComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	InventorySlots.SetNum(10);
	
	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::AddItem(FDataTableRowHandle ItemRow)
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
			
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White,FString::Printf(TEXT("+ 1 %s"), *ItemRow.RowName.ToString()));
			return true;
		}
	}
	return false;
}

void UInventoryComponent::SelectSlot(int NewIndex)
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

FString UInventoryComponent::GetItemNameFromSlot(const FInventorySlot& Slot)
{
	if (!Slot.ItemRow.DataTable)
		return "Empty";
	
	FItemData* ItemData = Slot.ItemRow.GetRow<FItemData>("GetItemName");
	
	if (!ItemData)
		return "Invalid";
	
	return ItemData->ItemName;
}

int UInventoryComponent::GetItemQuantity(const FInventorySlot& Slot)
{
	if (!Slot.ItemRow.DataTable)
		return 0;
	
	FItemData* ItemData = Slot.ItemRow.GetRow<FItemData>("GetItemQuantity");
	
	if (!ItemData)
		return -1;
	
	return Slot.Quantity;
}

EItemType UInventoryComponent::GetItemType(const FInventorySlot& Slot)
{
	if (!Slot.ItemRow.DataTable || !Slot.ItemRow.RowName.IsValid())
	{
		return EItemType::Standard;
	}
	
	FItemData* ItemData = Slot.ItemRow.DataTable->FindRow<FItemData>(Slot.ItemRow.RowName, TEXT("GetItemType"));
	
	if (!ItemData)
		 return EItemType::Standard;
	
	return ItemData->ItemType;
}

bool UInventoryComponent::HasItem(FName RowName) const
{
	for (const FInventorySlot& Slot : InventorySlots)
	{
		if (Slot.Quantity > 0 && Slot.ItemRow.RowName == RowName)
		{
			return true;
		}
	}
	return false;
}

void UInventoryComponent::EquipActorItem(const FItemData& ItemData, AFPSTemplateCharacter* Character)
{
	if (!ItemData.EquipActorClass)
		return;
	
	EquippedActor = GetWorld()->SpawnActor<AActor>(ItemData.EquipActorClass);
	if (!EquippedActor)
		return;
	
	EquippedActor->AttachToComponent(Character->GetMesh1P(),FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("GripPoint"));
	
	if (UTP_WeaponComponent* WeaponComponent = EquippedActor->FindComponentByClass<UTP_WeaponComponent>())
	{
		WeaponComponent->AttachWeapon(Character);
		Character->CurrentWeapon = WeaponComponent;
		Character->SetupPlayerInputComponent(Character->InputComponent);
	}
}

void UInventoryComponent::ApplyConsumableEffect(const FItemData* ItemData, AFPSTemplateCharacter* Character)
{
	if (UEffectComponent* Effects = Character->FindComponentByClass<UEffectComponent>())
	{
		Effects->ApplyEffect(
			ItemData->GrantedEffect,
			ItemData->EffectMagnitude,
			ItemData->EffectDuration,
			ItemData->EffectTickInterval,
			false);
	}
}

void UInventoryComponent::RemoveOneFromSlot(int32 SlotIndex)
{
	FInventorySlot& Slot = InventorySlots[SlotIndex];
	Slot.Quantity--;
	
	if (Slot.Quantity <= 0)
	{
		Slot.ItemRow = FDataTableRowHandle();
	}
}

void UInventoryComponent::EquipSelectedItem()
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
	
	AFPSTemplateCharacter* Character = Cast<AFPSTemplateCharacter>(GetOwner());
	if (!Character) return;
	
	switch (ItemData->ItemType)
	{
	case EItemType::Gun:
		EquipActorItem(*ItemData, Character);
		break;
		
	case EItemType::Consumable:
		break;
		
	case EItemType::Key:
		//door checks inventory
		break;
	
	case EItemType::Standard:
	default:
		break;
	}
}

void UInventoryComponent::CheckCurrentSlot(const FInventorySlot& Slot)
{
	if (InventorySlots.IsValidIndex(SelectedSlotIndex))
	{
		if (&InventorySlots[SelectedSlotIndex] == &Slot)
		{
			SelectSlot(SelectedSlotIndex);
		}
	}
}

void UInventoryComponent::DropItem()
{
	
	if (!InventorySlots.IsValidIndex(SelectedSlotIndex))
		return;
	
	FInventorySlot& Slot = InventorySlots[SelectedSlotIndex];
	if (Slot.Quantity <= 0)
		return;
	
	FItemData* ItemData = Slot.ItemRow.GetRow<FItemData>("DropItem");
	if (!ItemData)
		return;
	
	AFPSTemplateCharacter* Character = Cast<AFPSTemplateCharacter>(GetOwner());
	if (!Character)
		return;
	
	FVector Forward = Character->GetActorForwardVector();
	FVector SpawnLocation = Character->GetActorLocation() + Forward * 200.f + FVector(0,0,25.f);
	FRotator SpawnRotation = Character->GetActorRotation();
	

	if (AItem* DroppedItem = GetWorld()->SpawnActor<AItem>(BaseItem, SpawnLocation, SpawnRotation))
	{
		DroppedItem->InitializeItem(Slot.ItemRow);
	}
	
	Slot.Quantity--;
	
	if (Slot.Quantity <= 0)
	{
		Slot.ItemRow = FDataTableRowHandle(); //Slot Clear
	}
	
	if (EquippedActor)
	{
		EquippedActor->Destroy();
		EquippedActor = nullptr;
	}
	
}

void UInventoryComponent::UseSelectedItem()
{
	if (!InventorySlots.IsValidIndex(SelectedSlotIndex))
		return;
	
	FInventorySlot& Slot = InventorySlots[SelectedSlotIndex];
	if (Slot.Quantity <= 0)
		return;
	
	FItemData* ItemData = Slot.ItemRow.GetRow<FItemData>("UseSelectedItem");
	if (!ItemData)
		return;
	
	AFPSTemplateCharacter* Character = Cast<AFPSTemplateCharacter>(GetOwner());
	if (!Character) 
		return;
	
	switch (ItemData->ItemType)
	{
	case EItemType::Consumable:
		ApplyConsumableEffect(ItemData, Character);
		RemoveOneFromSlot(SelectedSlotIndex);
		break;
		
	case EItemType::Key:
		
		break;
		
	default:
		break;
	}
}



