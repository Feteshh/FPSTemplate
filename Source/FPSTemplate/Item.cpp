// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "FaceCameraTextRenderComponent.h"



// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Model"));
	RootComponent = Model;
	
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Item Collider"));
	Collider->SetupAttachment(Model);
	
	ItemTextDisplay = CreateDefaultSubobject<UFaceCameraTextRenderComponent>(TEXT("Item Text Display"));
	ItemTextDisplay->SetupAttachment(Model);	
	
}

// Called when the game starts or when spawned
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

	if (ItemTextDisplay)
	{
		if (FItemData* ItemData =
			ItemRow.GetRow<FItemData>("InitializeItem"))
		{
			ItemTextDisplay->UpdateTitle(
				ItemData->ItemName,
				RarityColor[ItemData->Rarity]
			);
		}
	}
}





