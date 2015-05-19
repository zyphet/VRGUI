// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/VRWidget.h"
#include "VRButton.generated.h"

/**
*
*/
UCLASS()
class VR_GUI_API AVRButton : public AVRWidget
{
	GENERATED_BODY()

	AVRButton(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaSeconds) override;

public:
	void SetButtonText(FString TextString);
	void SetTextRelativeLocation(FVector Loc);
	void SetTextScale(FVector Scale);
	void SetButtonColor(FVector Color);
	void SetTextColor(FVector Color);

	bool ButtonClicked();

	UStaticMeshComponent* Button;
	UMaterialInstanceDynamic* ButtonMat;

	bool bClicked;
	UTextRenderComponent* ButtonText;

};