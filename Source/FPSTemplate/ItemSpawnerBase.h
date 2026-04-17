// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "GameFramework/Actor.h"
#include "ItemSpawnerBase.generated.h"

UCLASS(Abstract)
class FPSTEMPLATE_API AItemSpawnerBase : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AItemSpawnerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	AItem* SpawnItem(const FDataTableRowHandle& RowHandle) const;

public:	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<AItem> BaseItem;
};
