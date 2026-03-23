// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextRenderComponent.h"
#include "FaceCameraTextRenderComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPSTEMPLATE_API UFaceCameraTextRenderComponent : public UTextRenderComponent
{
	GENERATED_BODY()
	UFaceCameraTextRenderComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
	UFUNCTION(BlueprintCallable)
	void UpdateTitle(FString ItemName, FColor TextColor);
	
};
