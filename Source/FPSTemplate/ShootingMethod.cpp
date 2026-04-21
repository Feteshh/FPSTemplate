#include "ShootingMethod.h"

#include "ShootingPattern.h"

void UShootingMethod::FireOneShot_Implementation(const FVector& Start, const FVector& Direction)
{
	if (!ShootingPattern)
	{
		FireSingle(Start, Direction);
		return;
	}
	
	TArray<FVector> Directions = ShootingPattern->GenerateDirections(Direction);
	
	for (const FVector& Dir : Directions)
	{
		FireSingle(Start, Direction);
	}
}

void UShootingMethod::FireSingle(const FVector& Start, const FVector& Direction)
{
	
}
