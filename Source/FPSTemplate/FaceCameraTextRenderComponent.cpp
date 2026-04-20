// Fill out your copyright notice in the Description page of Project Settings.


#include "FaceCameraTextRenderComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UFaceCameraTextRenderComponent::UFaceCameraTextRenderComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UFaceCameraTextRenderComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
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
			SetRelativeRotation(lookAt);
		}
	}
}

void UFaceCameraTextRenderComponent::UpdateTitle(FString ItemName, FColor TextColor)
{
	SetText(FText::FromString(ItemName));
	SetTextRenderColor(TextColor);
}
