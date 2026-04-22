// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "LockedDoor.generated.h"

UCLASS()
class FPSTEMPLATE_API ALockedDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALockedDoor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	TArray<FName> RequiredKeys;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	UStaticMeshComponent* DoorMesh;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherOverlappedComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	UBoxComponent* TriggerCollider;
	
	void OpenDoor();
	
};
