// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecificItemSpawner.h"

#include "ItemTextDisplay.h"

// Sets default values
ASpecificItemSpawner::ASpecificItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpecificItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	FItemData newItemData;
	
	if (specificItem.DataTable)
	{
		newItemData = *specificItem.GetRow<FItemData>("");
		
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();
		
		AItem* newItem = GetWorld()->SpawnActor<AItem>(baseItem,SpawnLocation,SpawnRotation);
		
		if (newItem)
		{
			newItem->itemDetail = newItemData;
			if (newItem->ItemTextDisplay)
				newItem->ItemTextDisplay->UpdateTitle(newItem->itemDetail.ItemName,newItem->RarityColor[newItemData.Rarity]);
		}
	}
}

// Called every frame
void ASpecificItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

