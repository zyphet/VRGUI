// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "VRCanvas.h"
#include "VRPawn.generated.h"

/**
 * 
 */
UCLASS()
class VR_GUI_API AVRPawn : public APawn
{
	GENERATED_BODY()
	
	AVRPawn(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	//Acts as root (wont actually collide with things)
	USphereComponent* CollisionComp;

	AVRCanvas* PlayerCanvas;

	void MouseClick();
	void MouseRelease();
	void ResetOculus();
	void ToggleOculusCursor();
	void Exit();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

public:
	AVRCanvas* GetCanvas();
};
