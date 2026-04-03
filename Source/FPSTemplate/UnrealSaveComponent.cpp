// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealSaveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MySaveGame.h"

// Sets default values for this component's properties
UUnrealSaveComponent::UUnrealSaveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	


	// ...
}


// Called when the game starts
void UUnrealSaveComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (UGameplayStatics::DoesSaveGameExist(TEXT("TestSaveSlot"),0))
	{
		Load();
	}
	else
	{
		Save();
	}
}


// Called every frame
void UUnrealSaveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUnrealSaveComponent::Save()
{
	UMySaveGame* mySaveGameInstance;
	mySaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	
	mySaveGameInstance->PlayerTransform = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorTransform();
	mySaveGameInstance->CameraRotation = GetWorld()->GetFirstPlayerController()->GetControlRotation();
	
	UGameplayStatics::SaveGameToSlot(mySaveGameInstance,TEXT("TestSaveSlot"),0);
}

void UUnrealSaveComponent::Load()
{
	
	UMySaveGame* myLoadGameInstance;
	myLoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	myLoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("TestSaveSlot"),0));
	GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorTransform(myLoadGameInstance->PlayerTransform);
	GetWorld()->GetFirstPlayerController()->SetControlRotation(myLoadGameInstance->CameraRotation);
}
