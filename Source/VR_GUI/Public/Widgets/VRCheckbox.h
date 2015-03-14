// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VRWidget.h"
#include "VRCheckbox.generated.h"

/**
*
*/
UCLASS()
class VR_GUI_API AVRCheckbox : public AVRWidget
{
	GENERATED_BODY()
	
	AVRCheckbox(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaSeconds) override;

	class UStaticMeshComponent* CheckboxMesh;
	class UStaticMeshComponent* CheckMesh;

	bool bChecked;

public:
	void ToggleCheck();
	bool IsChecked();

};