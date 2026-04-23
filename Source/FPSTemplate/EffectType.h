#pragma once

UENUM(BlueprintType)
enum class EEffectType : uint8
{
	None,
	Poison,
	Burn,
	ScarletRot,
	HealOverTime,
	Heal,
	ClearDebuff,
	IncreaseSize,
	SpeedBoost,
	HighJump
};
