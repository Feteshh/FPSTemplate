// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Components/ActorComponent.h"


#include "StringSaver.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSTEMPLATE_API UStringSaver : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStringSaver();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FString fileName = "myStringSave.txt";
	FString folderName = "SaveGame/";
	FString pathName;
	FString saveLocation;
	FVector savedPlayerPosition;
	FString saveData;
public:
	UFUNCTION(BlueprintCallable, Category = "Saving")
		bool Save();
	UFUNCTION(BlueprintCallable, Category = "Saving")
		bool Load();
	bool FileSave(FString SaveTextB, FString FileNameB);
	bool FileLoad(FString FileNameA, FString & SaveTextA);
	
	FString ItemDataToJSON(FItemData itemToConvert);
	FItemData JSOnToItemData(FString stringToConvert);
};
