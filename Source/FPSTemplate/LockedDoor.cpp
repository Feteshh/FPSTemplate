// Fill out your copyright notice in the Description page of Project Settings.


#include "LockedDoor.h"

#include "FPSTemplateCharacter.h"
#include "InventoryComponent.h"

// Sets default values
ALockedDoor::ALockedDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;
	
	TriggerCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerCollider"));
	TriggerCollider->SetupAttachment(RootComponent);
	TriggerCollider->OnComponentBeginOverlap.AddDynamic(this, &ALockedDoor::OnOverlapBegin);
}


void ALockedDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherOverlappedComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFPSTemplateCharacter* Character = Cast<AFPSTemplateCharacter>(OtherActor);
	if (!Character) return;
	
	UInventoryComponent* InventoryComponent = Character->Inventory;
	if (!InventoryComponent) return;
	
	for (const FName& KeyName : RequiredKeys)
	{
		if (!InventoryComponent->HasItem(KeyName))
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red,
				FString::Printf(TEXT("Missing Key: %s"), *KeyName.ToString()));
			return;
		}
	}
	OpenDoor();
}

void ALockedDoor::OpenDoor()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Door Unlocked!"));
	
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += 90.f;
	SetActorRotation(NewRotation);
}


