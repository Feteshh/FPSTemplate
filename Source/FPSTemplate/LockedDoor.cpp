// Fill out your copyright notice in the Description page of Project Settings.


#include "LockedDoor.h"

#include "FPSTemplateCharacter.h"
#include "InventoryComponent.h"

// Sets default values
ALockedDoor::ALockedDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;
	
	TriggerCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerCollider"));
	TriggerCollider->SetupAttachment(RootComponent);
	TriggerCollider->OnComponentBeginOverlap.AddDynamic(this, &ALockedDoor::OnOverlapBegin);
}

void ALockedDoor::BeginPlay()
{
	Super::BeginPlay();
	
	ClosedLocation = GetActorLocation();
	OpenedLocation = ClosedLocation + OpenOffset;
}

void ALockedDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector Current = GetActorLocation();
	FVector Target = IsOpen ? OpenedLocation : ClosedLocation;
	
	FVector NewLocation = FMath::VInterpConstantTo(Current,Target,DeltaTime,SlideSpeed);
	SetActorLocation(NewLocation);
}


void ALockedDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherOverlappedComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsLocked) return;
	
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
	IsLocked = false;
	IsOpen = true;
	
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Door Unlocked!"));
	
	GetWorld()->GetTimerManager().SetTimer(
		DoorTimerHandle,
		this,
		&ALockedDoor::CloseDoor,
		OpenDuration,
		false);
}

void ALockedDoor::CloseDoor()
{
	IsOpen = false;
	IsLocked = true;
	
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Door Locked!"));
}


