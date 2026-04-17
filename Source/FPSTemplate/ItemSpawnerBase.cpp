/// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawnerBase.h"

// Sets default values
AItemSpawnerBase::AItemSpawnerBase()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
}

// Called when the game starts or when spawned
void AItemSpawnerBase::BeginPlay()
{
	Super::BeginPlay();
}

AItem* AItemSpawnerBase::SpawnItem(const FDataTableRowHandle& RowHandle) const
{
	if (!BaseItem)
		return nullptr;
	
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	
	AItem* NewItem = GetWorld()->SpawnActor<AItem>(BaseItem, SpawnLocation, SpawnRotation);
	
	if (NewItem)
		NewItem->InitializeItem(RowHandle);
	
	return NewItem;
}


