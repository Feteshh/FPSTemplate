// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TextRenderComponent.h"
#include "ItemTextDisplay.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPSTEMPLATE_API UItemTextDisplay : public USceneComponent
{
	GENERATED_BODY()

public:	
	UItemTextDisplay();
	
	// Sets default values for this component's properties


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void UpdateTitle(FString ItemName, FColor TextColor);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextRenderComponent* Text;
};
