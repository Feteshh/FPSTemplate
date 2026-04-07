// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_PickUpComponent.h"

#include "Item.h"

UTP_PickUpComponent::UTP_PickUpComponent()
{
	// Set up the Sphere Collision
	SphereRadius = 32.f;
}

void UTP_PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UTP_PickUpComponent::OnSphereBeginOverlap);
}

void UTP_PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AFPSTemplateCharacter* Character = Cast<AFPSTemplateCharacter>(OtherActor);
	if(!Character)
		return;


	UInventory* Inventory = Character->FindComponentByClass<UInventory>();

	if (!Inventory)
		return;
	
	AItem* ItemActor = Cast<AItem>(GetOwner());
	
	if (!ItemActor)
		return;
	

	if (Inventory->AddItem(ItemActor->ItemRow))
	{
		OnPickUp.Broadcast(Character);

		GetOwner()->Destroy();
	}
}
