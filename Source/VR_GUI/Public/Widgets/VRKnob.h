// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/VRWidget.h"
#include "VRKnob.generated.h"

/**
 * 
 */
UCLASS()
class VR_GUI_API AVRKnob : public AVRWidget
{
	GENERATED_BODY()
	
	AVRKnob(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaSeconds) override;

public:
	bool ButtonClicked();

	float GetAngle();
	
private:
	class UStaticMeshComponent* Button;
	class UStaticMeshComponent* Ring;
	class UStaticMeshComponent* Marker;

	UMaterialInstanceDynamic* ButtonMat;

	void MoveMarker();

	float KnobAngle;

	bool bClicked;
	
};
