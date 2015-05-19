// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/VRWidget.h"
#include "VRLockDial.generated.h"

/**
 * 
 */
UCLASS()
class VR_GUI_API AVRLockDial : public AVRWidget
{
	GENERATED_BODY()
	
	// Sets default values for this actor's properties
	AVRLockDial(const FObjectInitializer& ObjectInitializer);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

public:
	bool ButtonClicked();

private:
	UClass* Dial;

	class UStaticMeshComponent* Button;
	class UStaticMeshComponent* Ring;

	UMaterialInstanceDynamic* ButtonMat;

	bool bClicked;
	
};
