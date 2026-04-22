// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "FaceCameraTextRenderComponent.h"



// Sets default values
AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Model"));
	RootComponent = Model;
	
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Item Collider"));
	Collider->SetupAttachment(Model);
	
	ItemTextDisplay = CreateDefaultSubobject<UFaceCameraTextRenderComponent>(TEXT("Item Text Display"));
	ItemTextDisplay->SetupAttachment(Model);	
}

void AItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	InitializeItem(ItemRow);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItem::InitializeItem(FDataTableRowHandle NewItemRow)
{
	ItemRow = NewItemRow;

	if (!ItemTextDisplay) return;

	if (FItemData* ItemData = ItemRow.GetRow<FItemData>("InitializeItem"))
	{
		const FColor* ColorPointer = RarityColor.Find(ItemData->Rarity);
		FColor Color = ColorPointer ? *ColorPointer : FColor::White;
		
		ItemTextDisplay->UpdateTitle(ItemData->ItemName, Color);
	}
		
}





