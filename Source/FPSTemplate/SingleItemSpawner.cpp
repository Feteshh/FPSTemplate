// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleItemSpawner.h"
// Called when the game starts or when spawned
void ASingleItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	if (SpecificItem.DataTable)
		SpawnItem(SpecificItem);
}

