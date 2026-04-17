// Fill out your copyright notice in the Description page of Project Settings.


#include "AllItemsSpawner.h"


// Called when the game starts or when spawned
void AAllItemsSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	if (!ItemTable) return;
	
	TArray<FName> RowNames = ItemTable->GetRowNames();
	
	for (int i = 0; i < RowNames.Num(); i++)
	{
		FDataTableRowHandle RowHandle;
		RowHandle.DataTable = ItemTable;
		RowHandle.RowName = RowNames[i];
		
		FVector SpawnLocation = GetActorLocation()+ FVector(i * 50.f, 0.f, 0.f);
		FRotator SpawnRotation = GetActorRotation();

		if (AItem* NewItem = GetWorld()->SpawnActor<AItem>(BaseItem, SpawnLocation, SpawnRotation))
			NewItem->InitializeItem(RowHandle);
		
	}
}
