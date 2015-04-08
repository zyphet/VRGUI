// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/VRWidget.h"
#include "VRText.generated.h"

/**
 * 
 */
UCLASS()
class VR_GUI_API AVRText : public AVRWidget
{
	GENERATED_BODY()
	
	AVRText(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	
public:
	void SetText(FString);

private:
	FString WidgetText;

	class UTextRenderComponent* Text;

};
