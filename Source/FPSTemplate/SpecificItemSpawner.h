// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "GameFramework/Actor.h"
#include "SpecificItemSpawner.generated.h"

UCLASS()
class FPSTEMPLATE_API ASpecificItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpecificItemSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AItem> baseItem;
	
	UPROPERTY(EditAnywhere)
	FDataTableRowHandle specificItem;
};
