// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemTextDisplay.h"

#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UItemTextDisplay::UItemTextDisplay()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	
	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Item Title"));
	Text->SetupAttachment(this);
	Text->SetText(FText::FromString("Base Text"));
}


// Called when the game starts
void UItemTextDisplay::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void UItemTextDisplay::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	UWorld* world = GetWorld();
	if (world)
	{
		APlayerCameraManager* CameraManager = 
			UGameplayStatics::GetPlayerCameraManager(world, 0);
		if (CameraManager)
		{
			FVector cameraLoc = CameraManager->GetCameraLocation();
			
			FRotator lookAt = UKismetMathLibrary::FindLookAtRotation(
				 GetOwner()->GetActorLocation(),
				cameraLoc);
			Text->SetWorldRotation(lookAt);
		}
	}
}

void UItemTextDisplay::UpdateTitle(FString ItemName, FColor TextColor)
{
	if (!Text)
		return;
	
	Text->SetText(FText::FromString(ItemName));
	Text->SetTextRenderColor(TextColor);
		
}