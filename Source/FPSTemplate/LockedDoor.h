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
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere)
    	UStaticMeshComponent* DoorMesh;
	
	UPROPERTY(visibleAnywhere)
    	UBoxComponent* TriggerCollider;
	
	UPROPERTY(EditAnywhere, Category = "Door")
	TArray<FName> RequiredKeys;
	
	UPROPERTY(EditAnywhere, Category = "Door")
	float OpenDuration = 3.f;
	
	UPROPERTY(EditAnywhere, Category = "Door")
	float SlideSpeed = 200.f;
	
	UPROPERTY(EditAnywhere, Category = "Door")
	FVector OpenOffset = FVector(0, 0, 200);
	
	bool DoorOpen = false;
	bool Locked = true;
	
	FVector ClosedLocation;
	FVector OpenedLocation;
	
	FTimerHandle DoorTimerHandle;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherOverlappedComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void OpenDoor();
	void CloseDoor();
};
