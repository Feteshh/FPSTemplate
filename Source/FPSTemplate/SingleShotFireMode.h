// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireMode.h"
#include "SingleShotFireMode.generated.h"


UCLASS(EditInlineNew)
class FPSTEMPLATE_API USingleShotFireMode : public UFireMode
{
	GENERATED_BODY()
	
public:
	virtual void Fire_Implementation() override;
	
};
