// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "Item.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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

void UInventory::TryPickupItem(FItemData ItemToAdd)
{
	if (MaxItemCount > MyItems.Num())
	{
		PickupItem(ItemToAdd);
	}
	else 
		UE_LOG(LogTemp, Warning, TEXT("Inventory Full"));
}

void UInventory::PickupItem(FItemData ItemToAdd)
{
	UE_LOG(LogTemp, Log, TEXT("item picked up"));
}

void UInventory::DropItem()
{
	UE_LOG(LogTemp, Log, TEXT("item picked dropped"));
}

