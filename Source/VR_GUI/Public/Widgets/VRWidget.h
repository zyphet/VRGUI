// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "VRWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR_GUI_API AVRWidget : public AActor
{
	GENERATED_BODY()

public:
	AVRWidget(const FObjectInitializer& ObjectInitializer);

	FVector GetWidgetCanvasCoords();

	FString GetWidgetName();

	void SetWidgetName(FString name);
	void SetWidgetLocation(FVector loc, float X, float Y);
	void SetWidgetScale(FVector scale);

	void WidgetClicked(UPrimitiveComponent* ComponentClicked);
	void WidgetClickRelease();

	bool bWidgetVisibility;

protected:
	FString WidgetName;

	//World Location
	FVector WidgetLocation;
	FVector WidgetScale;

	//Canvas Coords
	float CoordX;
	float CoordY;

	bool bWidgetClicked;
	UPrimitiveComponent* ComponentClicked;
};