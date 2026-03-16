// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"

#include "ItemTextDisplay.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
 	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	
	
}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	FItemData NewItemData;
	
	TArray<FItemData*> ItemList;
	
	ItemTable->GetAllRows("", ItemList);
	
	for (int i = 0; i < ItemList.Num(); i++)
	{
		NewItemData = *ItemList[i];
		
		FVector spawnLocation = GetActorLocation() + FVector(50 * i ,0,0);
		FRotator spawnRotation = GetActorRotation();
		
		AItem* newItem = GetWorld()->SpawnActor<AItem>(BaseItem,spawnLocation,spawnRotation);
		
		if (newItem)
		{
			
			newItem->itemDetail = NewItemData;
			if (newItem->ItemTextDisplay)
			newItem->ItemTextDisplay->UpdateTitle(NewItemData.ItemName ,newItem->RarityColor[NewItemData.Rarity]);
		}
	}
	
}
