// Fill out your copyright notice in the Description page of Project Settings.


#include "LootTableSpawner.h"

void ALootTableSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	const FLootEntry* Entry = LootTable.GetRandomEntry();
	if (!Entry)
		return;
	
	if (!Entry->Item.DataTable || Entry->Item.RowName.IsNone())
	{
		return;
	}
	SpawnItem(Entry->Item);
}
