// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "VRWidget.h"
#include "VRCheckbox.h"
#include "VRSlider.h"
#include "VRButton.h"
#include "VRKnob.h"
#include "VRCanvas.generated.h"

USTRUCT()
struct FWidgetLayer
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray<AVRWidget*> WidgetsInLayer;

	UPROPERTY()
	FString LayerName;

	bool bLayerVisible;

	FWidgetLayer()
	{
		LayerName = "";
		bLayerVisible = true;
	}
};

UCLASS()
class VR_GUI_API AVRCanvas : public AActor
{
	GENERATED_BODY()

	AVRCanvas(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	class UStaticMeshComponent* CanvasMesh;
	UMaterialInstanceDynamic* CanvasMat;

	//Array of Widgets on Canvas
	UPROPERTY()
	TArray<AVRWidget*> WidgetArray;
	UPROPERTY()
	TArray<FWidgetLayer> WidgetLayers;
	UPROPERTY()
	FWidgetLayer AlwaysVisibleLayer;

	//-----Widget Bindings-----//
	AVRCheckbox* VisibilityCheckbox;
	AVRSlider* RedSlider;
	AVRSlider* GreenSlider;
	AVRSlider* BlueSlider;
	AVRSlider* TransparencySlider;
	AVRButton* ToggleLayerButton;

	FLinearColor CanvasColor;

	void CenterCanvas();

	void UpdateCanvasProperties();

public:

	void AddWidget(AVRWidget* AWidget, float X, float Y, FString Name);
	void AddWidget(AVRWidget* AWidget, float X, float Y, FString Name, FString LayerName);
	
	void AddWidgetLayer(FString Name, bool bVisible);
	FWidgetLayer* GetWidgetLayer(FString Name);
	void SetWidgetLayerVisibility(FString LayerName, bool bValue);
	void SetWidgetLayerVisibility(FWidgetLayer &LayerName, bool bValue);
	void ToggleVisibleLayers();

	void BindWidgetToVisibility(AVRWidget* VisibilityWidget);
	void BindWidgetToRed(AVRWidget* RedWidget);
	void BindWidgetToBlue(AVRWidget* BlueWidget);
	void BindWidgetToGreen(AVRWidget* GreenWidget);
	void BindWidgetToTransparency(AVRWidget* TransparencyWidget);
	void BindWidgetToLayerToggle(AVRWidget* LayerButton);

	//Increase Canvas Scale by 1 = 10uu larger
	float DistanceFromViewer;
	float CanvasSizeX;
	float CanvasSizeY;

	FVector ConvertToWorldCoords(float X, float Y);
	void ResizeCanvas(float X, float Y, float Z);
	void SetCanvasColor(FLinearColor NewColor);

};
