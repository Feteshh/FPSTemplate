// Fill out your copyright notice in the Description page of Project Settings.


#include "StringSaver.h"

#include "JsonObjectConverter.h"
#include "MediaShaders.h"

// Sets default values for this component's properties
UStringSaver::UStringSaver()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStringSaver::BeginPlay()
{
	Super::BeginPlay();

	pathName = FPaths::ProjectSavedDir();
	saveLocation = pathName + folderName + fileName;
	
	Save();
	
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	
	// ...
	
}


// Called every frame
void UStringSaver::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UStringSaver::FileSave(FString SaveTextB, FString FileNameB)
{
	return FFileHelper::SaveStringToFile(SaveTextB, *(FileNameB));
}

bool UStringSaver::FileLoad(FString FileNameA, FString& SaveTextA)
{
	return FFileHelper::LoadFileToString(SaveTextA, *(FileNameA));
}

FString UStringSaver::ItemDataToJSON(FItemData itemToConvert)
{
	FString jsonString;
	FJsonObjectConverter::UStructToJsonObjectString(itemToConvert, jsonString, 0,0);
	return jsonString;
}

FItemData UStringSaver::JSOnToItemData(FString stringToConvert)
{
	FItemData RestoredItemData;
	FJsonObjectConverter::JsonObjectStringToUStruct(stringToConvert, &RestoredItemData,0,0);
	FJsonObjectConverter::JsonObjectStringToUStruct(stringToConvert, &RestoredItemData,0,0);
	return RestoredItemData;
}

bool UStringSaver::Save()
{
	savedPlayerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	
	saveData = savedPlayerPosition.ToString();
	
	return FileSave(saveData, saveLocation);
}

bool UStringSaver::Load()
{
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	if (FileManager.FileExists(*saveLocation))
	{
		if (FileLoad(saveLocation, saveData))
		{
			GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(savedPlayerPosition);
			return true;
		}
	}
	return false;
}

