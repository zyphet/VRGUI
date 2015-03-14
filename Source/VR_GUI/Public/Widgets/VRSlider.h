// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/VRWidget.h"
#include "VRSlider.generated.h"

/**
 * 
 */
UCLASS()
class VR_GUI_API AVRSlider : public AVRWidget
{
	GENERATED_BODY()
	
	AVRSlider(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaSeconds) override;
	
	class UStaticMeshComponent* SliderStart;
	class UStaticMeshComponent* SliderEnd;
	class UStaticMeshComponent* SliderBar;
	class UStaticMeshComponent* SliderBall;

	float LengthOfBarWorldUnits;
	float SliderBallPosition;

	//These components are empty, they simply
	//exist to mark the locations of the start and
	//end of the bar to make things easier.
	USceneComponent* StartOfBar;
	USceneComponent* EndOfBar;

	//0 to 1, based on where the ball is located
	float PositionPercent;

	void UpdatePositionAttribute();
	void MoveSlider();

public:

	float GetPositionPercent();
	void ChangeSliderLength(float BarLength);
};
