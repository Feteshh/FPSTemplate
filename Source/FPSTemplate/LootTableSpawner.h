// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSpawnerBase.h"
#include "LootTableSpawner.generated.h"

USTRUCT(BlueprintType)
struct FLootEntry
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle Item;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight = 1.f;
};

USTRUCT(BlueprintType)
struct FLootTable
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	
	TArray<FLootEntry> Entries;
	
	const FLootEntry* GetRandomEntry() const
	{
		if (Entries.Num() == 0)
		{
			UE_LOG(LogTemp, Error, TEXT("No entries found"));
			return nullptr;
		}
		
		float TotalWeight = 0.f;
		for (const FLootEntry& Entry : Entries)
			TotalWeight += Entry.Weight;
		
		float Roll = FMath::FRandRange(0.f, TotalWeight);
		float Accum = 0.f;
		
		for (int i = 0; i < Entries.Num(); ++i)
		{
			const FLootEntry& Entry = Entries[i];
			Accum += Entry.Weight;
			
			if (Roll <= Accum)
			{
				return &Entry;
			}
		}
		return nullptr;
	}
};

UCLASS()
class FPSTEMPLATE_API ALootTableSpawner : public AItemSpawnerBase
{
	GENERATED_BODY()
	
public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLootTable LootTable;
	
	protected:
	virtual void BeginPlay() override;
};
