// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Camera/CameraActor.h"
#include "VRCanvas.h"
#include "VRCursor.h"
#include "VRController.generated.h"

/**
 * 
 */
UCLASS()
class VR_GUI_API AVRController : public APlayerController
{
	GENERATED_BODY()

	AVRController(const FObjectInitializer& ObjectInitializer);
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UWorld* World;

	bool bUsingOculus;
	bool bValidOculus;
	ACameraActor* CurrentCamera;

	//Use looking direction as cursor, otherwise mouse
	bool bUseOculusCursor;

	//Used for mouse in oculus
	float VirtualMouseLocationX;
	float VirtualMouseLocationY;

	//Used for monitor mouse control
	FVector MouseLocation;
	FVector MouseDirection;

	float VirtualMouseSensitivity;

	FVector VirtualMouseWorldLocation;

	//Trace Variables
	FHitResult OutHit;
	FVector StartOfTrace;
	FVector EndOfTrace;
	FCollisionQueryParams Params;
	FCollisionResponseParams ResponseParam;

	//This variable currently isn't used
	//It might not be necessary to have, but I will.
	//Leave it here for now in case its useful later.
	AVRWidget* ClickedWidget;

	//Cursor
	AVRCursor* Cursor;

	void ProjectCursor();

public:

	void MouseClicked();
	void MouseReleased();
	void ToggleOculusCursor();

	//Canvas Coordinates
	FVector GetCanvasMouseLocation();

	FVector OculusPosition;
	FQuat OculusOrientation;
};
