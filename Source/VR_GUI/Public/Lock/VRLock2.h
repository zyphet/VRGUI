// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "VRCanvas.h"
#include "VRPawn.h"
#include "VRController.h"
#include "VRWidget.h"
#include "VRSlider.h"
#include "VRKnob.h"
#include "VRLockDial.h"
#include "VRText.h"
#include "VRLock2.generated.h"

UCLASS()
class VR_GUI_API AVRLock2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVRLock2();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:

	//Canvas the app will reside in
	AVRCanvas* PlayerCanvas;

	//The combination password
	int32 CombinationVal1;
	int32 CombinationVal2;
	int32 CombinationVal3;

	int32 EnteredComboVal1;
	int32 EnteredComboVal2;
	int32 EnteredComboVal3;

	AVRSlider* ComboSlider1;
	AVRSlider* ComboSlider2;
	AVRSlider* ComboSlider3;

	AVRText* CombinationText1;
	AVRText* CombinationText2;
	AVRText* CombinationText3;

	AVRLockDial* LockDial;

	TArray<FString> ButtonTextArray;

	AVRButton* DialButton0;
	AVRButton* DialButton1;
	AVRButton* DialButton2;
	AVRButton* DialButton3;
	AVRButton* DialButton4;
	AVRButton* DialButton5;
	AVRButton* DialButton6;
	AVRButton* DialButton7;
	AVRButton* DialButton8;
	AVRButton* DialButton9;
	
	void ResetEnteredValues();
	bool CheckCode();
};
