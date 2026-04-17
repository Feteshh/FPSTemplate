// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSpawnerBase.h"
#include "GameFramework/Actor.h"
#include "AllItemsSpawner.generated.h"

UCLASS()
class FPSTEMPLATE_API AAllItemsSpawner : public AItemSpawnerBase
{
	GENERATED_BODY()

public: UPROPERTY(EditAnywhere)
	UDataTable* ItemTable;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
