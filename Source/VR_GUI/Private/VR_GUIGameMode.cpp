// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_GUI.h"
#include "VR_GUIGameMode.h"
#include "VRController.h"
#include "VRPawn.h"

AVR_GUIGameMode::AVR_GUIGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerControllerClass = AVRController::StaticClass();
	DefaultPawnClass = AVRPawn::StaticClass();
}


