// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingTarget.h"

#include "HealthComponent.h"


// Sets default values
AShootingTarget::AShootingTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = Mesh;
	
	Mesh->SetCollisionProfileName("BlockAll");
	
	Health = CreateDefaultSubobject<UHealthComponent>("Health");
	Effects = CreateDefaultSubobject<UEffectComponent>("Effects");
}

// Called when the game starts or when spawned
void AShootingTarget::BeginPlay()
{
	Super::BeginPlay();
	
	InitialLocation = GetActorLocation();
	InitialRotation = GetActorRotation();
	
	Health->OnDeath.AddDynamic(this, &AShootingTarget::OnDeath);
}

void AShootingTarget::ApplyDamage_Implementation(float Amount)
{
	Health->ApplyDamage(Amount);
	
	if (Effects->HasEffect(EEffectType::Poison))
	{
		Mesh->SetVectorParameterValueOnMaterials("TintColor", FVector(0,1,0));
	}
}

void AShootingTarget::OnDeath()
{
	Mesh->SetSimulatePhysics(true);
	
	FTimerHandle ResetTimer;
	
	GetWorld()->GetTimerManager().SetTimer(ResetTimer,[this]()
	{
		Mesh->SetSimulatePhysics(false);
		
		SetActorLocation(InitialLocation);
		SetActorRotation(InitialRotation);
		
		Health->ApplyHealing(9999.f);
		Effects->RemoveAllEffects();
	},2.f,false);
}

