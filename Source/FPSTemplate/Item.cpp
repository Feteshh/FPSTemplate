// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "ItemTextDisplay.h"



// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Model"));
	RootComponent = Model;
	
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Item Collider"));
	Collider->SetupAttachment(Model);
	
	ItemTextDisplay = CreateDefaultSubobject<UItemTextDisplay>(TEXT("Item Text Display"));
	ItemTextDisplay->SetupAttachment(Model);	
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	//ItemTextDisplay->UpdateTitle(itemDetail.ItemName,RarityColor[itemDetail.Rarity]);
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}



// void AItem::UpdateTitle()
// {
// 	
// 	
// 	if (Text)
// 	{
// 		Text->SetText(FText::FromString(itemDetail.ItemName));
// 		Text->SetTextRenderColor(RarityColor[itemDetail.Rarity]);
// 	}
// }


