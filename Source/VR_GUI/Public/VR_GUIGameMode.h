// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "VRLock.h"
#include "VR_GUIGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VR_GUI_API AVR_GUIGameMode : public AGameMode
{
	GENERATED_BODY()

	AVR_GUIGameMode(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
};
