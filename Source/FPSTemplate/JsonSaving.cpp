// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonSaving.h"

#include "Item.h"
#include "JsonObjectConverter.h"

// Sets default values for this component's properties
UJsonSaving::UJsonSaving()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UJsonSaving::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UJsonSaving::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FString UJsonSaving::ItemDataToJSON(FItemData itemToConvert)
{
	FString jsonString;
	FJsonObjectConverter::UStructToJsonObjectString(itemToConvert, jsonString, 0,0);
	return jsonString;
}

FItemData UJsonSaving::JSOnToItemData(FString stringToConvert)
{
	FItemData RestoredItemData;
	FJsonObjectConverter::JsonObjectStringToUStruct(stringToConvert, &RestoredItemData,0,0);
	FJsonObjectConverter::JsonObjectStringToUStruct(stringToConvert, &RestoredItemData,0,0);
	return RestoredItemData;
}
