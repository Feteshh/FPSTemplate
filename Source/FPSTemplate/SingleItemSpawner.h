// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ItemSpawnerBase.h"
#include "GameFramework/Actor.h"
#include "SingleItemSpawner.generated.h"

UCLASS()
class FPSTEMPLATE_API ASingleItemSpawner : public AItemSpawnerBase
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere)
	FDataTableRowHandle SpecificItem;

protected:
	virtual void BeginPlay() override;
};
