// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "VRCanvas.h"
#include "VRPawn.h"
#include "VRController.h"
#include "VRWidget.h"
#include "VRSlider.h"
#include "VRKnob.h"
#include "VRText.h"
#include "VRLock.generated.h"

UCLASS()
class VR_GUI_API AVRLock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVRLock(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

public:


private:

	void BindSliderToText(AVRSlider* Slider, AVRText* Text);

	//Canvas the app will reside in
	AVRCanvas* PlayerCanvas;

	//The combination password
	int32 CombinationVal1;
	int32 CombinationVal2;
	int32 CombinationVal3;

	//Current value for lock
	int32 KnobCurrentValue;

	//The widgets needed for the app
	AVRKnob* LockKnob;

	AVRSlider* ComboSlider1;
	AVRSlider* ComboSlider2;
	AVRSlider* ComboSlider3;

	AVRText* CombinationText1;
	AVRText* CombinationText2;
	AVRText* CombinationText3;

	AVRText* LockDisplay1;
	AVRText* LockDisplay2;
	AVRText* LockDisplay3;

	AVRText* CurrentValue;
	
};
