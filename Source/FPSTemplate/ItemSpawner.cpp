// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"

#include "FaceCameraTextRenderComponent.h"
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
	
	
	TArray<FName> RowNames = ItemTable->GetRowNames();
	
	for (int i = 0; i < RowNames.Num(); i++)
	{
		FDataTableRowHandle RowHandle;
		RowHandle.DataTable = ItemTable;
		RowHandle.RowName = RowNames[i];
		
		FVector spawnLocation = GetActorLocation() + FVector(50 * i ,0,0);
		FRotator spawnRotation = GetActorRotation();
		
		AItem* newItem = GetWorld()->SpawnActor<AItem>(BaseItem,spawnLocation,spawnRotation);
		
		if (newItem)
		{
			newItem->InitializeItem(RowHandle);
		}
	}
	
}
